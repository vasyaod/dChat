#ifndef DWINDOW_H
#define DWINDOW_H

#include <QtGui>

class dWindowFrame;
class dChatApplication;
class dSetting;
class dSettingWindow;

class dWindow : public QObject
{
    Q_OBJECT
    private:
    // Пункт меню, который показывает видимость этого окна.
        QAction *windowAct;
    // Указаель на рамку окна.
        dWindowFrame *windowFrame;
    // Указатель на приложение.
        dChatApplication *application;
    // Настройки окна.        
        dSetting *settingWindow;
        
    public:
        dWindow(const QString &settingKey, dWindowFrame *_windowFrame, QObject *_parent = 0 );
        ~dWindow();
    
    // Возвращает QAction этого окна.
        QAction *getWindowAct()const{ return windowAct; };
    // Методы устанавливают свойства окон.
        void setTitle( const QString & _title );
        void setIcon( const QIcon & _icon );
    // Метод возвращает настройки окна.
        dSetting *getSettingWindow()const{ return settingWindow; };
    // Если нужно прорисовать окно при старте.
        void start();
        
    public slots:
        void hide();        
        void show();
        void lower();
        void setVisible( bool _visible );
        bool isVisible() const;
        
    signals:
    // Сигнал посылается в том случаи если нужно сообщить окну пользователей
    // о том что закрылось окно канала.
        void hideSignal( bool checked = false );
};
#endif // DWINDOW_H
