#include <QtGui>

#include <algorithm>
#include <math.h>
#include "dwindowframe.h"
#include "dpixmapbutton.h"
#include "dpixmapview.h"

/****************************************************************
    КЛАСС dWindowFrame
    По сути является рамкой окна. Обеспечивает вывод рамки, заго-
 ловка и статус-бара.
     Описание а файле: dwindowframe.h
*****************************************************************/

// Инициализация статистической переменной dwindows_list, active_windows_list и 
// dwindows_connection.
QList<QWidget*> dWindowFrame::dwindows_list;
QList<dWindowConnection> dWindowConnection::dwindows_connection;

//***************************************************************
// НАБОР КОНСТРУКТОРОВ.
dWindowFrame::dWindowFrame(QWidget *parent): 
        QWidget(parent),
        title_visibility(true),  // По умолчанию, заголовок окна виден.
        magnet(10),              // По умолчанию, степень магнитизации 10.
        leading(false),          // По умолчанию, окно не является ведущим.
        min_button_visible(true),// По умолчанию, кнопка сворачивания окна видна.
        max_button_visible(true), // По умолчанию, кнопка развертывания окна видна.
        independented(false)     // Окно зависимое... связано с другими...
{   
    
//****************************************************************
// Создаем ШАПКУ.
    hat_left_image  = new dPixmapView();
    hat_left_image->setMaximumSize(0,0);
    hat_center_image = new dPixmapView();    
    hat_center_image->setMaximumSize(0,0);
    hat_right_image  = new dPixmapView();
    hat_right_image->setMaximumSize(0,0);

//****************************************************************
// Создаем кнопки(закрить, минимизация...) в шапке.
    close_button = new dPixmapButton();
    close_button->setMaximumSize(0,0);
    min_button = new dPixmapButton();
    min_button->setMaximumSize(0,0);
    max_button = new dPixmapButton();
    max_button->setMaximumSize(0,0);
// Будем перехватывать сигналы от кнопак.
    connect(close_button, SIGNAL(clicked()), this, SLOT(pressClosedKey()));
    connect(min_button, SIGNAL(clicked()), this, SLOT(pressMinimizedKey()));
    connect(max_button, SIGNAL(clicked()), this, SLOT(pressMaximizedKey()));

//****************************************************************
// Скомпануем шапку.

    QHBoxLayout *hat_center_layout = new QHBoxLayout;
    hat_center_layout->setMargin(0);
    hat_center_layout->setSpacing(0);
    hat_center_layout->addSpacing(0);
    hat_center_layout->addItem( new QSpacerItem(1,1, QSizePolicy::Expanding, QSizePolicy::Minimum) );
    hat_center_layout->addSpacing(0);    
    hat_center_layout->addWidget(min_button);
    hat_center_layout->addWidget(max_button);
    hat_center_layout->addWidget(close_button);
    hat_center_layout->addSpacing(0);
    hat_center_image->setLayout(hat_center_layout);

    QHBoxLayout *hat_layout = new QHBoxLayout;
    hat_layout->setMargin(0);
    hat_layout->addWidget(hat_left_image);
    hat_layout->addWidget(hat_center_image);
    hat_layout->addWidget(hat_right_image);

//****************************************************************
// Создаем рамку в цетре.
    frame_left = new dPixmapView();
    frame_left->setMaximumSize(0,0xFFFFFF);
    frame_right = new dPixmapView();
    frame_right->setMaximumSize(0,0xFFFFFF);

    QHBoxLayout *center_layout = new QHBoxLayout;
    center_layout->setMargin(0);
    center_layout->addWidget(frame_left);

    center_frame = new dEmptyFrame();
   // frame_2->setFrameShape(QFrame::StyledPanel);
   // center_frame->setFrameShadow(QFrame::Raised);
    center_frame->setBackgroundRole(QPalette::Background);
    center_layout->addWidget(center_frame);
    center_layout->addWidget(frame_right);
  
//****************************************************************
// Создаем статус-бар.   
    status_bar_left = new dPixmapView();
    status_bar_left->setMaximumSize(0,0);
    status_bar_center = new dPixmapView();
    status_bar_center->setMaximumSize(0xFFFFFF,0);
// Кнопка изменения размеров.    
    status_bar_right = new dWindowFrameResize(QPixmap());
    status_bar_right->setMaximumSize(0,0);    
    
    QHBoxLayout *bottom_layout = new QHBoxLayout;
    bottom_layout->setMargin(0);
    bottom_layout->addWidget(status_bar_left);
    bottom_layout->addWidget(status_bar_center);
    bottom_layout->addWidget(status_bar_right);

// Скомпануем слои, и получим всю рамку целиком.     
    QVBoxLayout *window_layout = new QVBoxLayout;
    window_layout->setSpacing(0);
    window_layout->setMargin(0);
    window_layout->addItem(hat_layout);
    window_layout->addItem(center_layout);
    window_layout->addItem(bottom_layout);

    QWidget::setLayout(window_layout);
 
  // task_bar_window = new QWidget(0,Qt::Window);
  // task_bar_window->resize(100,100);
 //   this->setParent(task_bar_window);
  //  task_bar_window->move(0xFFFFFF,0xFFFFFF);
 //   task_bar_window->setWindowOpacity(0);
 //   task_bar_window->show();
 //   setWindowFlags(Qt::FramelessWindowHint);
//    */
   // skin_ini_file = tr("window-skin/default/window-skin.ini");
   // setSkin(skin_ini_file);
}

void dWindowFrame::clearSkin()
{
    bool _visible = isVisible();
    setVisible(false);
    setWindowFlags(Qt::Widget);

    QSize nullSize(0,0);
    QPixmap nullPixmap(nullSize);
    
    pm_hat_left_active = QPixmap(nullSize);
    pm_hat_left_not_active = QPixmap(nullSize);
    pm_hat_center_active = QPixmap(nullSize);
    pm_hat_center_not_active = QPixmap(nullSize);
    pm_hat_right_active = QPixmap(nullSize);
    pm_hat_right_not_active = QPixmap(nullSize);
   
    hat_left_image->setPixmap(nullPixmap);
    hat_left_image->setMaximumSize(nullSize);
    hat_left_image->setFixedSize(nullSize); 
    hat_center_image->setPixmap(nullPixmap);
    hat_center_image->setMaximumSize(nullSize);
    hat_center_image->setFixedSize(nullSize); 
    hat_right_image->setPixmap(nullPixmap);
    hat_right_image->setMaximumSize(nullSize);
    hat_right_image->setFixedSize(nullSize); 
    
    close_button->setOverButton(nullPixmap);
    close_button->setDisabledButton(nullPixmap);
    close_button->setPressedButton(nullPixmap);
    close_button->setButton(nullPixmap);
    close_button->setMaximumSize(nullSize);
    close_button->setFixedSize(nullSize); 
    
    min_button->setOverButton(nullPixmap);
    min_button->setDisabledButton(nullPixmap);
    min_button->setPressedButton(nullPixmap);
    min_button->setButton(nullPixmap);
    min_button->setMaximumSize(nullSize);
    min_button->setFixedSize(nullSize); 
    
    max_button->setOverButton(nullPixmap);
    max_button->setDisabledButton(nullPixmap);
    max_button->setPressedButton(nullPixmap);
    max_button->setButton(nullPixmap);
    max_button->setMaximumSize(nullSize);
    max_button->setFixedSize(nullSize); 

    frame_left->setPixmap(nullPixmap);
    frame_left->setMaximumSize(nullSize);
    frame_left->setFixedSize(nullSize); 
    frame_right->setPixmap(nullPixmap);
    frame_right->setMaximumSize(nullSize);
    frame_right->setFixedSize(nullSize); 

    status_bar_left->setPixmap(nullPixmap);
    status_bar_left->setMaximumSize(nullSize);
    status_bar_left->setFixedSize(nullSize); 
    status_bar_center->setPixmap(nullPixmap);
    status_bar_center->setMaximumSize(nullSize);
    status_bar_center->setFixedSize(nullSize); 

    status_bar_right->setDisabledButton(nullPixmap);
    status_bar_right->setButton(nullPixmap);
    status_bar_right->setOverButton(nullPixmap);
    status_bar_right->setPressedButton(nullPixmap);
    status_bar_right->setMaximumSize(nullSize);
    status_bar_right->setFixedSize(nullSize); 

    setVisible(_visible);
}

void dWindowFrame::setSkin( const QString &_skin_ini_file )
{

    bool _visible = isVisible();
    setVisible(false);
    setWindowFlags(Qt::SplashScreen);
    skin_ini_file = _skin_ini_file;
// Найдем каталог в котором лежат скины.
    QDir dir(_skin_ini_file);
    dir.cd( ".." );
    skin_dir = dir.path();
    skin_dir += "/";

// Прочитаем файл с настройками "скина".
    QSettings skin(_skin_ini_file, QSettings::IniFormat);    

    skin.beginGroup("main");
    if( skin.value("title-visibility","on").toString() == "off" )
    {
         hat_center_image->setText(QString(""));
         title_visibility = false;
    }
    else
        title_visibility = true;
        
    skin.endGroup();
//****************************************************************
// Загружаем картинки с изображением шапки.
    skin.beginGroup("hat-active");
    pm_hat_left_active.load(skin_dir+skin.value("left").toString());
    pm_hat_center_active.load(skin_dir+skin.value("center").toString());
    pm_hat_right_active.load(skin_dir+skin.value("right").toString());
    skin.endGroup();

    skin.beginGroup("hat-not-active");
    pm_hat_left_not_active.load(skin_dir+skin.value("left").toString());
    pm_hat_center_not_active.load(skin_dir+skin.value("center").toString());
    pm_hat_right_not_active.load(skin_dir+skin.value("right").toString());
    skin.endGroup();

//Прорисуем шапку.
    
    hat_left_image->setPixmap(pm_hat_left_active);
    hat_center_image->setPixmap(pm_hat_center_active);
    hat_right_image->setPixmap(pm_hat_right_active);
    
    hat_left_image->setFixedSize(hat_left_image->sizeHint()); 
    hat_center_image->setMaximumSize(0xFFFFFF,hat_center_image->getPixmap().height());
//  Устанавливается ниже.
//    hat_center_image->setMinimumSize(hat_center_image->getPixmap().width(),hat_center_image->getPixmap().height());
    hat_right_image->setFixedSize(hat_right_image->sizeHint()); 

    
//  Выведем заголовок, если нужно.
    if ( title_visibility )
    { 
        // Установим шрифты.
        QFont title_font = getFontWindowTitle();
        title_font.setBold(true);
        setFontWindowTitle(title_font);
        // Найдем, куда нужно впичатывать заголовок окна.
        int title_position_y = hat_center_image->height()/2 + title_font.pointSize()/2;
        int title_position_x = 5;
        skin.beginGroup("title");
        title_position_y= skin.value("position-y",title_position_y).toInt();
        title_position_x= skin.value("position-x",title_position_x).toInt();
        skin.endGroup();      
        // Выведем заголовок.
        hat_center_image->setText(title_position_x,title_position_y,windowTitle());
    }
//****************************************************************
// Закрашиваем кнопки в шапке.    
    skin.beginGroup("close-button");
        close_button->setOverButton(QPixmap(skin_dir+skin.value("over").toString()));
        close_button->setDisabledButton(QPixmap(skin_dir+skin.value("disabled").toString()));
        close_button->setPressedButton(QPixmap(skin_dir+skin.value("pressed").toString()));
        close_button->setButton(QPixmap(skin_dir+skin.value("main").toString()));
        close_button->setFixedSize(close_button->sizeHint()); 
    skin.endGroup();
    skin.beginGroup("min-button");
        min_button->setOverButton(QPixmap(skin_dir+skin.value("over").toString()));
        min_button->setDisabledButton(QPixmap(skin_dir+skin.value("disabled").toString()));
        min_button->setPressedButton(QPixmap(skin_dir+skin.value("pressed").toString()));
        min_button->setButton(QPixmap(skin_dir+skin.value("main").toString()));
        min_button->setFixedSize(min_button->sizeHint()); 
    skin.endGroup();
    if( !min_button_visible )
        min_button->setFixedSize(0,0); 
    
    skin.beginGroup("max-button");
        max_button->setOverButton(QPixmap(skin_dir+skin.value("over").toString()));
        max_button->setDisabledButton(QPixmap(skin_dir+skin.value("disabled").toString()));
        max_button->setPressedButton(QPixmap(skin_dir+skin.value("pressed").toString()));
        max_button->setButton(QPixmap(skin_dir+skin.value("main").toString()));
        max_button->setFixedSize(max_button->sizeHint()); 
    skin.endGroup();
    if( !max_button_visible )
        max_button->setFixedSize(0,0); 

//    hat_center_image->setMinimumSize(close_button->getPixmap().width()+
//                                     min_button->getPixmap().width()+
//                                     max_button->getPixmap().width()+30,
//                                     hat_center_image->getPixmap().height());

    hat_center_image->setMinimumSize(close_button->getPixmap().width()+
                                     (min_button_visible ? min_button->getPixmap().width():0)+
                                     (max_button_visible ? max_button->getPixmap().width():0),
                                     hat_center_image->getPixmap().height()
					);

//Прорисуем шапку.
    isVisible() ? activate() : deactivate();  

//****************************************************************
// Создаем рамку в цетре.
    skin.beginGroup("frame");

    frame_left->setPixmap(QPixmap(skin_dir+skin.value("left").toString()));
    frame_left->setMaximumSize(frame_left->getPixmap().width(),0xFFFFFF);
    frame_left->setMinimumSize(frame_left->getPixmap().width(),1);
    frame_right->setPixmap(QPixmap(skin_dir+skin.value("right").toString()));
    frame_right->setMaximumSize(frame_right->getPixmap().width(),0xFFFFFF);
    frame_right->setMinimumSize(frame_right->getPixmap().width(),1);
   
    skin.endGroup();

//****************************************************************
// Создаем статус-бар.    

    skin.beginGroup("status-bar");
    status_bar_left->setPixmap(QPixmap(skin_dir+skin.value("left").toString()));
    status_bar_left->setFixedSize(status_bar_left->sizeHint()); 
    status_bar_center->setPixmap(QPixmap(skin_dir+skin.value("center").toString()));
    status_bar_center->setMaximumSize(0xFFFFFF,status_bar_center->getPixmap().height());
    status_bar_center->setMinimumSize(1,status_bar_center->getPixmap().height());

// Кнопка изменения размеров.    
    status_bar_right->setButton(QPixmap(skin_dir+skin.value("right").toString()));
    status_bar_right->setOverButton(QPixmap(skin_dir+skin.value("right-over").toString()));
    status_bar_right->setPressedButton(QPixmap(skin_dir+skin.value("right-over").toString()));
    status_bar_right->setFixedSize(status_bar_right->sizeHint()); 
    status_bar_right->setStep(10,10);
    
    skin.endGroup();
    setVisible(_visible);
}
//***************************************************************
    // Назначим собственные слоты... их название говорит само за себя.
void dWindowFrame::pressMinimizedKey()
{
    emit minimized();
//    showMinimized();
};
void dWindowFrame::pressMaximizedKey()
{
//* Старая версия
    if( windowState() == Qt::WindowMaximized )
    {
        setWindowState(Qt::WindowNoState);        
    }
    else if( windowState() == Qt::WindowNoState )
    {
        emit maximized();
        setWindowState(Qt::WindowMaximized);
    }
 //   showMaximized();
// */
// Новая версия.
    emit maximized();
};

void dWindowFrame::pressClosedKey()
{
    emit closed();
//    close();
};

//***************************************************************
void dWindowFrame::setSizeIncrement( const QSize & _size )
{
    status_bar_right->setStep(_size);
};
void dWindowFrame::setSizeIncrement( int _width, int _height )
{
    status_bar_right->setStep(_width,_height);
};

uint dWindowFrame::getMagnet()
{
    return magnet;
};
void dWindowFrame::setMagnet( uint _magnet )
{
    magnet = _magnet;
};
void dWindowFrame::setLeading( bool _leading )
{
    leading = _leading;
};
bool dWindowFrame::getLeading()
{
    return leading;
};
void dWindowFrame::setMinButton( bool _min_button )
{
    min_button_visible = _min_button;
    if( !min_button_visible )
        min_button->setFixedSize(0,0); 
    else
        min_button->setFixedSize(min_button->sizeHint()); 
};
bool dWindowFrame::getMinButton()
{
    return min_button_visible;
};
void dWindowFrame::setMaxButton( bool _max_button )
{
    max_button_visible = _max_button;
    if( !max_button_visible )
        max_button->setFixedSize(0,0); 
    else
        max_button->setFixedSize(max_button->sizeHint()); 
};
bool dWindowFrame::getMaxButton()
{
    return max_button_visible;
};

void dWindowFrame::overloadMoveEvent( bool _overload )
{
   center_frame->overloadMoveEvent( _overload );
}
//***************************************************************
// ДЕСТРУКТОР.
dWindowFrame::~dWindowFrame()
{
    /* ПОКА ПУсТО */
   // cout << "DESTRUCT" << endl;
    dWindowConnection::dwindows_connection.removeAll(dWindowConnection(this,NULL));
    dwindows_list.removeAll(this);
}

void dWindowFrame::showEvent( QShowEvent * _event )
{
//    dwindows_list.removeAll(this);
    if( !independented )
        dwindows_list << this; // Добавим окно в список наших окон.
    checkConnection();
}

void dWindowFrame::hideEvent ( QHideEvent * _event )
{
   // cout << "hideEvent" << endl;
//***************************************************************
// При скрытии окна нужно убрать это его из списка окон, а также
// закрыть все соединения(если они конечно есть).
    dWindowConnection::dwindows_connection.removeAll(dWindowConnection(this,NULL));
    dwindows_list.removeAll(this);
  //  task_bar_window->hide();
}
//***************************************************************
// Делает окно активным, то есть меняет картинки в шапке.
void dWindowFrame::activate()
{
    hat_left_image->setPixmap(pm_hat_left_active);
    hat_center_image->setPixmap(pm_hat_center_active);
    hat_right_image->setPixmap(pm_hat_right_active);
    close_button->setActive(true);
    min_button->setActive(true);    
    max_button->setActive(true);    

   // task_bar_window->hide();
};

//***************************************************************
// Делает окно НЕ активным, то есть меняет картинки в шапке.
void dWindowFrame::deactivate()
{

    hat_left_image->setPixmap(pm_hat_left_not_active);
    hat_center_image->setPixmap(pm_hat_center_not_active);
    hat_right_image->setPixmap(pm_hat_right_not_active);
    close_button->setActive(false);
    min_button->setActive(false); 
    max_button->setActive(false); 

//    task_bar_window->show();
    //task_bar_window->setWindowTitle(this->windowTitle());
//    task_bar_window->lower();
};

void dWindowFrame::setFontWindowTitle( const QFont & _title_font )
{
    hat_center_image->setFont(_title_font);
}

const QFont &dWindowFrame::getFontWindowTitle() const
{
    return hat_center_image->getFont();
}

void dWindowFrame::mousePressEvent ( QMouseEvent * e )
{
    dx = e->globalX() - pos().x();
    dy = e->globalY() - pos().y();
//******************************************************************
// При нажитии копки мыши, формируется список окон которые соединены с
// текущим окном. Если это окно не является ведущим, то этот список остается
// пустым.
    moveable_windows_list = QList<QWidget*>();
    QWidget* win = this;
    if( leading )
        dWindowConnection::globalFindWindows( (QWidget*)this , moveable_windows_list );
        
 //   cout << moveable_windows_list.size() << " - " << dwindows_list.size() << " - "
 //   << dWindowConnection::dwindows_connection.size() << endl;
    QWidget::mousePressEvent( e );
};

void dWindowFrame::mouseMoveEvent( QMouseEvent * e )
{
    moved = true;       // Покажем, что произошло перетаскивание окна.
    int delta;          // Вспомогательная переменная.
//****************************************************************
// ЭФФЕКТ МАГНИТА!!!
// Далее создается эфект примагничевания окон...
// Выглядит конечно жутко, но работает!!!

    QPoint new_pos;
    new_pos.rx() = e->globalX() - dx;
    new_pos.ry() = e->globalY() - dy;

    if( abs(new_pos.x()) < magnet )
        new_pos.rx() = 0;
    if( abs(new_pos.y()) < magnet )
        new_pos.ry() = 0;
    if( abs(desktop.width()-(new_pos.x()+width())) < magnet )
        new_pos.rx() = desktop.width()-width();
    if( abs(desktop.height()-(new_pos.y()+height()))< magnet )
        new_pos.ry() = desktop.height()-height();
        
    QListIterator<QWidget*> i(dwindows_list);
    while (i.hasNext())
    {
        QWidget * B = i.next();
        if( B != this && !moveable_windows_list.contains(B) )
        {
        
            delta = B->x() - (new_pos.x() + width());
            if ( abs(delta) < magnet  && new_pos.y()<(B->y()+B->height()+magnet)&&(new_pos.y()+height()+magnet)>B->y())
            {
                new_pos.rx() = new_pos.x()+delta;
                delta = B->y() - new_pos.y();
                if ( abs(delta) < magnet  )
                     new_pos.ry() = new_pos.y()+delta;
                delta = (B->y() + B->height())- (new_pos.y() + height());
                if ( abs(delta) < magnet  )
                     new_pos.ry() = new_pos.y()+delta;
            }
            
            delta = B->y() - (new_pos.y() + height());
            if ( abs(delta) < magnet && new_pos.x()<(B->x()+B->width()+magnet)&&(new_pos.x()+width()+magnet)>B->x())
            {
                new_pos.ry() = new_pos.y()+delta;
                delta = B->x() - new_pos.x();
                if ( abs(delta) < magnet  )
                     new_pos.rx() = new_pos.x()+delta;
                delta = (B->x() + B->width())- (new_pos.x() + width());
                if ( abs(delta) < magnet  )
                     new_pos.rx() = new_pos.x()+delta;
            }
            
            delta = ( B->x() + B->width() ) - new_pos.x();
            if ( abs(delta) < magnet && new_pos.y()<(B->y()+B->height()+magnet) && (new_pos.y()+height()+magnet)>B->y() )
            {
                new_pos.rx() = new_pos.x()+delta;
                delta = B->y() - new_pos.y();
                if ( abs(delta) < magnet  )
                     new_pos.ry() = new_pos.y()+delta;
                delta = (B->y() + B->height())- (new_pos.y() + height());
                if ( abs(delta) < magnet  )
                     new_pos.ry() = new_pos.y()+delta;
            }

            delta = ( B->y() + B->height() ) - new_pos.y();
            if ( abs(delta) < magnet && new_pos.x()<(B->x()+B->width()+magnet) && (new_pos.x()+width()+magnet)>B->x() )
            {
                new_pos.ry() = new_pos.y()+delta;
                delta = B->x() - new_pos.x();
                if ( abs(delta) < magnet  )
                     new_pos.rx() = new_pos.x()+delta;
                delta = (B->x() + B->width())- (new_pos.x() + width());
                if ( abs(delta) < magnet  )
                     new_pos.rx() = new_pos.x()+delta;

            }
        }
    }
    // Сохраним изменение размемеров.
    QPoint deltaPos = new_pos-pos();
    // Переместим перетаскиваемое окно.
    move(new_pos);    
    // Переместим все окна, которые находятся в прямой или косвенной связа с
    // эти окном.
    QList<QWidget*>::iterator iter;
    for (iter = moveable_windows_list.begin(); iter != moveable_windows_list.end(); ++iter)
    {
        QWidget* win = *iter;
        if(win != this )
           win->move(win->pos()+deltaPos);
    }
    
    QWidget::mouseMoveEvent( e );
};

//***********************************************************
// Вспомогательная функция. Проверяет наличие соединений с другими окнами,
// и если нужно его установить то она это делает.
void dWindowFrame::checkConnection()
{
        QPoint point = pos();
        int delta;
        
        // Если флаг равен true, то произошло примагничивание.
        bool magnet_flag = false;

        QListIterator<QWidget*> i(dwindows_list);
        while (i.hasNext())
        {
            QWidget * B = i.next();
            if( B != this )
            {            
                delta = B->x() - (point.x() + width());
                if ( abs(delta) < magnet  && point.y()<(B->y()+B->height()+1)&&(point.y()+height()+1)>B->y())
                    magnet_flag = true;     // Произошло примагничивание.
                
                delta = B->y() - (point.y() + height());
                if ( abs(delta) < magnet && point.x()<(B->x()+B->width())&&(point.x()+width())>B->x())
                    magnet_flag = true;     // Произошло примагничивание.
                
                delta = ( B->x() + B->width() ) - point.x();
                if ( abs(delta) < magnet && point.y()<(B->y()+B->height()+1) && (point.y()+height()+1)>B->y() )
                    magnet_flag = true;     // Произошло примагничивание.
    
                delta = ( B->y() + B->height() ) - point.y();
                if ( abs(delta) < magnet && point.x()<(B->x()+B->width()) && (point.x()+width())>B->x() )
                    magnet_flag = true;     // Произошло примагничивание.
    
                //****************************************************************
                // Смотрим есть-ли примагничивание чежду двумя окнами, и нужно ли
                // создавать соединение.
                if( magnet_flag == true )
                {
                    // Примагнителись.... создаем соединение.
                    if(!dWindowConnection::dwindows_connection.contains(dWindowConnection(this,B))) 
                        dWindowConnection::dwindows_connection.push_back(dWindowConnection(this,B));
                }
                else
                    // Произошло размагничивание... удаляем соединение.
                    dWindowConnection::dwindows_connection.removeAll(dWindowConnection(this,B));
                magnet_flag = false;
            }
        }

};

void dWindowFrame::mouseReleaseEvent( QMouseEvent * _event )
{
//***********************************************************
// При отпусканни клавиши мыши, после перетаскивания окна,
// нужно посмотреть с какими окнами соеденино текущее окно,
// и если соединение не установлено, то создать его.
  
    if ( moved )
    {
        checkConnection();
    }
//    */
    moved = false;
    QWidget::mouseMoveEvent( _event );
}

bool dWindowFrame::event ( QEvent * _event )
{

    if( _event->type() == QEvent::WindowTitleChange )
    // Установим новый заголовок если нужно.
        if( title_visibility )
            hat_center_image->setText(windowTitle());
        
    if( _event->type() == QEvent::WindowActivate )
    {
        QList<QWidget*>::iterator iter;
        for (iter = dwindows_list.begin(); iter != dwindows_list.end(); ++iter)
        {
                QWidget* win = *iter;
                if( win != this )
                    win->raise();
        }
        this->raise();
        activate();
    }
    if( _event->type() == QEvent::WindowDeactivate )
        deactivate();
        
    return QWidget::event( _event );
};

// Установка центратьного Widget в наше окно.
void dWindowFrame::setCentralWidget ( QWidget *_widget )
{
    QHBoxLayout *layout = new QHBoxLayout;  // Создади в нем какой либо слой.
    layout->setMargin(0);
    layout->addWidget(_widget);
    center_frame->setLayout(layout);
};

// Установка центрального слоя в наше окно.
void dWindowFrame::setLayout ( QLayout *layout )
{
    center_frame->setLayout(layout);
};

dWindowFrame *dWindowFrame::make( QWidget *_parent  )
{
    return new dWindowFrame( _parent );
}
QString dWindowFrame::getSkin() const
{
     return skin_ini_file;
};

// Метод делает окно независимым, тоесть оно не прицепляется к себе подобным.
void dWindowFrame::setIndependent( bool _independented )
{
    independented = _independented;
    if( _independented )
        dwindows_list.removeAll(this);
    else
        dwindows_list.push_back(this);
};

/****************************************************************
    КЛАСС dWindowFrameResize
    Вспомогательный класс. Описывает кнопку увеличения размеров в
 рамке. Является потомком dPixmapButton.
    Описание в файле: dwindowframe.h
*****************************************************************/
dWindowFrameResize::dWindowFrameResize( const QPixmap &_pm_button,
                   QWidget *_parent):
        dPixmapButton(_pm_button,_parent)
{   
    step.rwidth() = 1;
    step.rheight() = 1;
    setCursor(Qt::SizeFDiagCursor);
};
void dWindowFrameResize::setStep( const QSize &_step )
{
    step = _step;
};
void dWindowFrameResize::setStep( int _width, int _height  )
{
    step.rwidth()   = _width;
    step.rheight()  = _height;
};
void dWindowFrameResize::mouseMoveEvent(QMouseEvent * e)
{
    QWidget * window = parentWidget();
//    QPoint p = window->pos();

    QSize s = window->size();
    s.rwidth() = int((e->globalX()-window->x())/step.rwidth()+1)*step.rwidth();
    s.rheight() = int((e->globalY()-window->y())/step.rheight()+1)*step.rheight();
    window->resize(s);
    
    /*
  //  qDebug()<<;
    if( abs( x - e->globalX()) >= step.rwidth()-1 )
    {
        QSize s = window->size();
        s.rwidth() = int((e->globalX()-window->x())/step.rwidth())*step.rwidth();
        window->resize(s);
        x = e->globalX();
    }

    if(abs( y - e->globalY()) >= step.rheight() )
    {
        QWidget * window = parentWidget();
        QSize s = window->size();
        s.rheight() = s.rheight() - (y - e->globalY());
        window->resize(s);
        y = e->globalY();
    }
    */
};

void dWindowFrameResize::mousePressEvent( QMouseEvent * e )
{   
    x = e->globalX();
    y = e->globalY();
};

/****************************************************************
    КЛАСС dWindowConnection
    Вспомогательный класс. Описывает соединение примагниченных окон.
 Содержит указатели пару окон которые находятся в соединеии друг с
 другом. По сути каждый обьект того класса описывает ребра графа,
 узлами которого являются окна(указатели на них).
*****************************************************************/
dWindowConnection::dWindowConnection(QWidget *_winA,QWidget *_winB)
{
    winA = _winA;
    winB = _winB;
}
bool dWindowConnection::operator ==( const dWindowConnection &_connection ) const
{
    if( winA == _connection.winA && winB == _connection.winB )
        return true;
    if( winB == _connection.winA && winA == _connection.winB )
        return true;
    if( winA == _connection.winA &&  _connection.winB == NULL)
        return true;
    if( winB == _connection.winA &&  _connection.winB == NULL)
        return true;
    if( winA == _connection.winB &&  _connection.winA == NULL)
        return true;
    if( winB == _connection.winB &&  _connection.winA == NULL)
        return true;

    return false;
};

bool dWindowConnection::operator ==( QWidget *_win ) const
{
    if( winA == _win )
        return true;
    if( winB == _win )
        return true;
    return false;
};

QList<QWidget*> dWindowConnection::findWindows( QWidget* _win )
{
    QList<QWidget*> win_list;

    QListIterator<dWindowConnection> i(dWindowConnection::dwindows_connection);
    while (i.hasNext())
    {
        const dWindowConnection &conn = i.next();
        if( conn.winA == _win )
            win_list << conn.winB;
        if( conn.winB == _win )
            win_list << conn.winA;
    }
    return win_list;
};

void dWindowConnection::globalFindWindows( QWidget* _win, QList<QWidget*>&_global_win_list )
{
    QList<QWidget*> win_list = findWindows( _win );
    _global_win_list << _win;

    QList<QWidget*>::iterator i;
    for (i = win_list.begin(); i != win_list.end(); ++i)
        if( !_global_win_list.contains(*i) )
            globalFindWindows( *i, _global_win_list );
};

/****************************************************************
    КЛАСС dEmptyFrame
    Вспомогательный класс.
    Класс описывает пустой фрейм(даже без рамки), который по 
 умолчанию заполняет все пространство в центре нашего окна.
 Его создание понадобилось, для того что бы перегрузить события
 мыши, которые не нужно наследовать от предка, то есть dWindowFrame.
*****************************************************************/
void dEmptyFrame::mousePressEvent ( QMouseEvent * _event )
{
    if ( overload )
    QFrame::mousePressEvent(_event);
};
void dEmptyFrame::mouseMoveEvent( QMouseEvent * _event )
{
    if ( overload )
        QFrame::mouseMoveEvent(_event);
};
void dEmptyFrame::mouseReleaseEvent ( QMouseEvent * _event )
{
    if ( overload )
        QFrame::mouseReleaseEvent(_event);
};  
void dEmptyFrame::overloadMoveEvent( bool _overload )
{
   overload = _overload;
}
