#ifndef DWARNINGWINDOW_H
#define DWARNINGWINDOW_H

#include <QtGui>

#include "../dwindow.h"
#include "../net/duser.h"

class dChatApplication;
class dSetting;
class dWarningWindow;
class dSettingWarning;

class dMessageWindow : public QWidget
{   
//    Q_OBJECT
    private:
    // Окно всплывающих сообщений....
        dWarningWindow *warningWindow;
    // Рамка окна....
        dWindowFrame *window;
        int closeTimerID;
        int opacityStartTimerID;
        int opacityTimerID;
    public:
        dMessageWindow( dWarningWindow *_warningWindow, const QString &_msg, dPUser _from, dPUser _to, int _timeOut, QColor &_bgcolor  );
        ~dMessageWindow();
            
   //     void setBgColor( const QColor &bgcolor);
    protected:
    // Тамер срабатывает, когда нужно уничтожить сообщение.
        virtual void timerEvent ( QTimerEvent * event );
//    public slots:
//        void slot_msg_channel( dPUser _from, const QString & _msg );
};

class dWarningWindow : public QObject
{   
    Q_OBJECT
    private:
    // Ук. на рамку окна.
        dWindowFrame *window;
    // Ук. главный класс приложения.
        dChatApplication *application;
    // Настройки окна.
        dSetting *settingWindow;
    // Слои куда будут втыкаться сообщения.
        QVBoxLayout *mainLayout;
    // Настройки предупреждений....
        dSettingWarning *settingWarning;
// 
//        QList<dMessageWindow*> messageList;
    // Содердит число показанных в данный монент времени сообщений.
        int messageCount;
    // Выдает нужноо сообщение или звук.
        dMessageWindow *warning( const QString &key,
                              const QString &_msg, 
                              dPUser _from = dPUser(), 
                              dPUser _to = dPUser());
    public:
        dWarningWindow( dWindowFrame *_window, QObject *_parent = 0);
        ~dWarningWindow();
        
        dWindowFrame *getWindowFrame(){ return window; }; 
        int &getMessageCount(){ return messageCount; };
    public slots:
    // Слоты вызываются при получении одноименных сообщений. cм dUser и dManagerEx.
        void slot_msg_channel( dPUser _from, const QString & _msg );
        void slot_msg_channel_me( dPUser _from, const QString & _msg );
        void slot_change_topic( const QString & _topic );
        void slot_msg_enter( dPUser _from );
        void slot_msg_exit( dPUser _from );
        void slot_msg_beep( dPUser _from, dPUser _to);
        void slot_msg_personal( dPUser _from, dPUser _to , const QString & _msg);
        void slot_msg_mass( dPUser _from, dPUser _to, const QString & _msg);
        void slot_msg_rename( dPUser _from, const QString &_oldname);
        void slot_msg_other( dPUser _from, dPUser _to, const QString & _msg);
};

#endif // DWARNINGWINDOW_H
