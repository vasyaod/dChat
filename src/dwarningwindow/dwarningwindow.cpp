#include "dwarningwindow.h"
#include "dsettingwarning.h"

#include "../dchatapplication.h"
#include "../dsettingwindow.h"
#include "../dwindowframe/dwindowframe.h"
#include "../dsetting.h"
#include "../dsettinggeneral.h"

dMessageWindow::dMessageWindow( dWarningWindow *_warningWindow, 
                                const QString &_msg, 
                                dPUser _from, 
                                dPUser _to, 
                                int _timeOut, 
                                QColor &_bgcolor  ):
        warningWindow(_warningWindow)
        
{
    warningWindow->getMessageCount()++;
    window = warningWindow->getWindowFrame();
    window->setWindowOpacity(1);
    window->raise();
  //  if( warningWindow->getMessageCount() == 1 )
   //     window->show();
    QPalette _palette = palette();
    _palette.setColor(QPalette::Disabled,QPalette::Background,_bgcolor);
    _palette.setColor(QPalette::Active,QPalette::Background,_bgcolor);
    _palette.setColor(QPalette::Inactive,QPalette::Background,_bgcolor);
    setPalette(_palette);
    
    QVBoxLayout *layout = new QVBoxLayout;

    layout->setMargin(2);
    layout->setSpacing(2);
    layout->addWidget(new QLabel(_msg) );

    if( _from == true )
    {
        QHBoxLayout *layoutFrom = new QHBoxLayout;
        layoutFrom->setMargin(0);
        layoutFrom->setSpacing(2);
        QLabel *fromLabel = new QLabel();
        fromLabel->setPixmap(_from->get_avatar().scaled(16,16));
        layoutFrom->addWidget(new QLabel(tr("От:")) );
        layoutFrom->addWidget(fromLabel );
        layoutFrom->addWidget(new QLabel(tr("%1 (IP:%2)").arg(_from->get_name()).arg(_from->get_ip().toString())) );
        layoutFrom->addStretch();
        layout->addItem(layoutFrom);
    }

    if( _to == true )
    {
        QHBoxLayout *layoutTo = new QHBoxLayout;
        layoutTo->setMargin(0);
        layoutTo->setSpacing(2);
        QLabel *toLabel = new QLabel();
        toLabel->setPixmap(_to->get_avatar().scaled(16,16));
        layoutTo->addWidget(new QLabel(tr("Для:")) );
        layoutTo->addWidget(toLabel );
        layoutTo->addWidget(new QLabel(tr("%1 (IP:%2)").arg(_to->get_name()).arg(_to->get_ip().toString())) );
        layoutTo->addStretch();
        layout->addItem(layoutTo);
    } 

    setLayout(layout);     
    layout->addStretch();
    
    int _height = window->height()+sizeHint().height()+1;
    window->setMinimumHeight( _height );
    window->setMaximumHeight( _height );
    window->resize(  QSize( window->width(), _height ) );

    closeTimerID = startTimer ( _timeOut * 1000 );
    opacityStartTimerID = startTimer ( _timeOut * 1000 - 1000 );
}
/*
void dMessageWindow::setBgColor( const QColor &bgcolor)
{
    window->repaint();
    repaint();
}
*/
dMessageWindow::~dMessageWindow()
{
    warningWindow->getMessageCount()--;
    int _height = window->height()-sizeHint().height()-1;
    window->setMinimumHeight( _height );
    window->resize(  QSize( window->width(), _height )  );
    if( warningWindow->getMessageCount() == 0 )
        window->setWindowOpacity(0);
    //    window->hide();
};

void dMessageWindow::timerEvent ( QTimerEvent * _event ) 
{
    if( opacityStartTimerID == _event->timerId () )
        opacityTimerID = startTimer ( 100 );
    if( opacityTimerID == _event->timerId () )
        if( warningWindow->getMessageCount() == 1)
           window->setWindowOpacity(window->windowOpacity()*0.9);
    if( closeTimerID == _event->timerId () )
        delete this;
}

dWarningWindow::dWarningWindow( dWindowFrame *_window, QObject *_parent ):
        window(_window),
        messageCount(0),
        QObject(_parent)
{
    
    application = qobject_cast<dChatApplication*>(QApplication::instance());
    setParent(application);
    // Поста

    settingWindow = new dSettingWindow(tr("warning_window"),application->settingWindow,window);
    settingWindow->setTitle(tr("Настройки стиля окна всплывающих предупреждений."));

    settingWarning = new dSettingWarning(tr("warning"),application->settingGeneral);
    settingWarning->setTitle(tr("Предупреждения"));
    settingWarning->setIcon(QIcon(tr("pic/plugin64x64.png")));   

    window->setWindowFlags(window->windowFlags()| Qt::WindowStaysOnTopHint);    
    window->setMinButton(false);        // Уберем кнопочку "свернуть".    
    window->setMaxButton(false);        // Уберем кнопочку "развернуть во весь экран.".    
    window->overloadMoveEvent(true);    // Можно таскать окно за любое место.
    window->setIndependent(true);       // Делаем окно независимым....
    
    
    QWidget *centralWidget = new QWidget();
    mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(1);
    centralWidget->setLayout(mainLayout);     
    window->setCentralWidget(centralWidget);
    
    window->resize(QSize(window->width(),window->minimumHeight()));
    
    window->setWindowOpacity(0);
    window->show();
}

dWarningWindow::~dWarningWindow()
{
    delete settingWindow;
};

void dWarningWindow::slot_msg_channel( dPUser _from, const QString & _msg )
{
    warning(tr("channel_warning"),tr("<b>Получено сообщение в канал.</b><br>%1").arg(_msg),_from);
};
void dWarningWindow::slot_change_topic( const QString & _topic )
{
    warning(tr("topic_warning"),tr("<b>Топик изменен.</b><br>%1").arg(_topic));
};
void dWarningWindow::slot_msg_channel_me( dPUser _from, const QString & _msg )
{
    warning(tr("channel_me_warning"),tr("<b>Шепот в канале.</b><br>%1").arg(_msg),_from);
};
void dWarningWindow::slot_msg_enter( dPUser _from )
{
    warning(tr("enter_warning"),tr("<b>В чат вощел пользователь.</b>"),_from);
};
void dWarningWindow::slot_msg_exit( dPUser _from )
{
    warning(tr("exit_warning"),tr("<b>Из чата вышел пользователь.</b>"),_from);
};
void dWarningWindow::slot_msg_beep( dPUser _from, dPUser _to)
{
    warning(tr("beep_warning"),tr("<b>Получен звуковой вызов.</b>"),_from,_to);
};
void dWarningWindow::slot_msg_personal( dPUser _from, dPUser _to, const QString & _msg )
{
    warning(tr("persnal_warning"),tr("<b>Получено сообщение.</b><br>%1").arg(_msg),_from,_to);
};
void dWarningWindow::slot_msg_mass( dPUser _from, dPUser _to, const QString & _msg )
{
    warning(tr("mass_warning"),tr("<b>Получено массовое сообщение.</b><br>%1").arg(_msg),_from,_to);
};
void dWarningWindow::slot_msg_rename( dPUser _from, const QString & _oldname )
{
    warning(tr("rename_warning"),tr("<b>Пользоваель переименовался.</b><br>Из: %1 <br>В: %2").arg(_oldname).arg(_from->get_name()),_from);
};
void dWarningWindow::slot_msg_other( dPUser _from, dPUser _to, const QString & _msg )
{
    QColor bgcolor(57,181,74);
    dMessageWindow*messageWindow = new dMessageWindow(this,_msg,_from,_to,5,bgcolor);
    mainLayout->addWidget(messageWindow);
};

dMessageWindow *dWarningWindow::warning( const QString &key, 
                              const QString &_msg, 
                              dPUser _from, 
                              dPUser _to)
{

    dMessageWindow *messageWindow =0;

    if( settingWarning->toInt(key,tr("window"),1 ) && 
        settingWarning->getMaxWindow() >= getMessageCount() )
    {
        QColor bgcolor(settingWarning->toInt(key,tr("color"),0xFFFFFF));
        messageWindow = new dMessageWindow(this,_msg,_from,_to,settingWarning->getWindowTimeOut(),bgcolor);
        mainLayout->addWidget(messageWindow);
    }    
    if( settingWarning->toInt(key,tr("sound"),1 ) )
        QSound::play( settingWarning->get(key,tr("sound_file"),tr("sound/sound.wav") ) );
   
    return messageWindow;
}


