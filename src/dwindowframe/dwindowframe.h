#ifndef DWINDOWFRAME_H
#define DWINDOWFRAME_H

#include <QtGui>

#include "dpixmapbutton.h"
#include "dpixmapview.h"

class dWindowFrame;         // Описан ниже.... В этом же файле. 
class dWindowFrameResize;   // Описан ниже.... В этом же файле.
class dWindowConnection;    // Описан ниже.... В этом же файле.
class dEmptyFrame;          // Описан ниже.... В этом же файле.

Q_DECLARE_INTERFACE(dWindowFrame,"dWindowFrame/1.0")

/****************************************************************
    КЛАСС dWindowFrame.
    Класс описывает окно с нестандартной рамкой, которая загружается
 из различных графических файлов(скиноф). Между окнами этого класса
 существует эфект магнитизма, то есть при близком сближении окон друг
 с другом они соединяются (эфект такой же как и у Winamp). Если
 какое либо окно обьявлено "ведущим" (метод setLeading), то при его 
 перемещении, будут так же перемещатся все соединенные с ним окна.
    Изменение разменров окна происхотит если тянуть за нижний
 правый угол.(если эта возможность предусмотрена скином!).
*****************************************************************/
class dWindowFrame : public QWidget
{
    Q_OBJECT
    Q_INTERFACES(dWindowFrame)
    private:
    // Список наших окошек(являются вершинами графов). 
        static QList<QWidget*> dwindows_list;          
    // Сохранение координат мыши, нужно для перемещения окна.
        int dx,dy;
    // Указывает на то что это окно независимое........ если independented = true
        bool independented;
    // Картинки с изображением шапки.
        QPixmap pm_hat_left_active;
        QPixmap pm_hat_left_not_active;
        QPixmap pm_hat_center_active;
        QPixmap pm_hat_center_not_active;
        QPixmap pm_hat_right_active;
        QPixmap pm_hat_right_not_active;
    // Указатели на разные части шапки. Нужны для изменения смены 
    // активности.
        dPixmapView *hat_left_image;
        dPixmapView *hat_center_image;
        dPixmapView *hat_right_image;
    // Указатели на кнопки в шапке.
        dPixmapButton *close_button;
        dPixmapButton *min_button;
        dPixmapButton *max_button;
    // Указатели на рамку;
        dPixmapView *frame_left;
        dPixmapView *frame_right;
    // Центральный Widget в нашем окне, заполняет все пространсктво в
    // цетре окна.
        dEmptyFrame *center_frame;  
    // Указатели на картинки со статус бара.
        dPixmapView *status_bar_left;
        dPixmapView *status_bar_center;
        dWindowFrameResize * status_bar_right;

    // Окно которое эмулирует появление окна в таск баре. 
     //   QWidget *task_bar_window;

    // Делает окно активным( НЕ активным), то есть меняет картинки 
    // в шапке.
        void activate();
        void deactivate();
    // Флаг, который показывает, нужно-ли отрожать заголовог окна.
        bool title_visibility;

        QString skin_dir;       // Директория, где лежит скин и ini-файл 
                                // c настройками.
        QString skin_ini_file;  // Имя ini-файла c настройками skin-а.
    
    // Степень магнитизации. Количество пикселей после которого срабатывает
    // примагничевание окон.
        int magnet;

    // Виджет рабочего стола, нужен что бы знать его длинну и ширину.
        QDesktopWidget desktop;

    // Флаг... устанавливается в true после перетаскивания окна. После 
    // отпускания левой клавиши мыши вновь устанавливется в false.
        bool moved;

    // Флаг показывает, ведущее ли это окно.
        bool leading;
    // Вспомогательная функция. Проверяет наличие соединений с другими окнами,
    // и если нужно его установить то она это делает.
        void checkConnection();
        
    // При нажитии копки мыши, формируется список окон которые соединены с
    // текущим окном. Если это окно не является ведущим, то этот список остается
    // пустым.
        QList<QWidget*> moveable_windows_list;          

    // Флаг определяет видимость кнопки сворачивания окна.
        bool min_button_visible;
    // Аналогично предидущему влагу, но только для кнопки развертывания.
        bool max_button_visible;
    
    protected slots:
    // Назначим собственные слоты... их название говорит само за себя.
         void pressMinimizedKey();
         void pressMaximizedKey();
         void pressClosedKey();
    
        
    protected:
    // Перегрузка событий. Унаследованных от предка QWidget.
        virtual void mousePressEvent ( QMouseEvent * _event );
        virtual void mouseMoveEvent( QMouseEvent * _event );
        virtual void mouseReleaseEvent ( QMouseEvent * _event );
        virtual bool event( QEvent * _event );
        virtual void hideEvent ( QHideEvent * event );
        virtual void showEvent ( QShowEvent * _event );        
        
    // Созданны сигналы, которые посылаются при закрытии окна(нажатие на кнопку
    // с крестом), при нажатии на кнопку сворачивания окна, и при нажатии на
    // кнопку развертывания окна во весь экран.
    signals:
        void minimized();
        void maximized();         
        void closed();

    public:
        dWindowFrame( QWidget *parent=0 );
    // Удевительно, но это деструктор.
        virtual ~dWindowFrame();

    // Возвращает степень магнитизации, то растояние в пикселях, на котором
    // происходит происходит примагничивание двух окон.
        virtual uint getMagnet();
    // Устанавливает степень магнитизации.
        virtual void setMagnet( uint _magnet );
    // Изменение шрифта заголовка окна.
        virtual void setFontWindowTitle( const QFont & _title_font );
    // Метод возвращает шрифт заголовка окна.
        virtual const QFont &getFontWindowTitle() const;
    // Установка скина рамки окна.
        virtual void setSkin( const QString &_skin_ini_file );
    // Метод возвращает имя файла с конфигурацией скина.
        virtual QString getSkin() const;
    // Метод очищает скин, и оставляет стандартное окно.
        virtual void clearSkin();
    // Установка центрального Widget-а посреди окна.
        virtual void setCentralWidget ( QWidget * widget );
    // Подсоединение центратьного слоя в наше окно.
        virtual void setLayout ( QLayout *layout );
    // Промежуток увеличения размеров. Растояние, через которое произойдет
    // следующее изменение размеров.
        virtual void setSizeIncrement( const QSize & _size );
        virtual void setSizeIncrement( int _width, int _height );
    // Делает это окно ведущим ( true - ведущее ).
    // Если окно ведущее, то при перетаскивании этого окна, будут так же
    // перемещатся все примагниченые к нему окна.
        virtual void setLeading( bool _leading = true );
        virtual bool getLeading();
    // Устанавливает видимость кнопки сворачивания окна.
        virtual void setMinButton( bool _min_button = true );
        virtual bool getMinButton();
    // Устанавливает видимость кнопки развертывания окна.
        virtual void setMaxButton( bool _max_button = true );
        virtual bool getMaxButton();
    // Устанавливает возможномть перемещать окно, держа его за любое место,
    // а не только за рамку.
        virtual void overloadMoveEvent( bool _overload = true );
    // Метод делает окно независимым, тоесть оно не примагничивается к себе подобным.
        virtual void setIndependent( bool _independented = true );

    // Создает новое окно... просто вызывает оператор new dWindowFrame( _parent ),
    // требуется для работы плагина Qt. Система загрузки плагинов может 
    // создавать только один объект этого класса, и нужно как то обходить
    // эту неприятность. Вот решение!
        virtual dWindowFrame *make( QWidget *_parent = 0);
        
};

/****************************************************************
    КЛАСС dWindowFrameResize
    Вспомогательный класс. Описывает кнопку увеличения размеров в
 рамке. Является потомком dPixmapButton.
*****************************************************************/
class dWindowFrameResize: public dPixmapButton
{
    private:
    // Координаты мыши.
        int x,y;
    // Шаг увеличения размеров.
        QSize step;
        
    protected:
    // Перегрузка событий.
        virtual void mousePressEvent( QMouseEvent * e );
        virtual void mouseMoveEvent( QMouseEvent * e );
    public:
        dWindowFrameResize( const QPixmap &_pm_button,
                            QWidget *_parent = 0);
        void setStep( const QSize &_step );
        void setStep( int _width, int _height );
        
};

/****************************************************************
    КЛАСС dWindowConnection
    Вспомогательный класс. Описывает соединение примагниченных окон.
 Содержит указатели пару окон которые находятся в соединеии друг с
 другом. По сути каждый обьект того класса описывает ребра графа,
 узлами которого являются окна(указатели на них).
*****************************************************************/
class dWindowConnection
{
    public:
    // Список соединений. 
        static QList<dWindowConnection> dwindows_connection;

        QWidget * winA;
        QWidget * winB;
    
        dWindowConnection(QWidget *_winA,QWidget *_winB);
        bool operator ==( const dWindowConnection& _connection ) const;
        bool operator ==( QWidget *_win ) const;
        
    // Поиск окон соединенных с указанным окном на прямую.
        static QList<QWidget*> findWindows( QWidget *_win );
    // Поиск окон соединенных с указанным окном на прямо или косвенно,
    // то есть посредством другого окна.
        static void globalFindWindows( QWidget *_win, QList<QWidget*>&_global_win_list );
};

/****************************************************************
    КЛАСС dEmptyFrame
    Вспомогательный класс.
    Класс описывает пустой фрейм(даже без рамки), который по 
 умолчанию заполняет все пространство в центре нашего окна.
 Его создание понадобилось, для того что бы перегрузить события
 мыши, которые не нужно наследовать от предка, то есть dWindowFrame.
*****************************************************************/
class dEmptyFrame: public QFrame
{
    private:
        bool overload;
    protected:    
        virtual void mousePressEvent ( QMouseEvent * _event );
        virtual void mouseMoveEvent( QMouseEvent * _event );
        virtual void mouseReleaseEvent ( QMouseEvent * _event );  
        
    public:
        void overloadMoveEvent( bool _overload = true );
        dEmptyFrame( QWidget *_parent = 0, Qt::WFlags _f = 0 ):
                QFrame(_parent,_f),overload(false){};
};

#endif // DWINDOWFRAME_H
