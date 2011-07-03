#ifndef DCHANNELWINDOW_H
#define DCHANNELWINDOW_H

#include <QtGui>

#include "../dwindow.h"
#include "../net/duser.h"

class dChatApplication;
class dSettingWindow;
class dSettingChannel;
class dMessageTable;

//********************************************************
// Пришлось исправить как
//********************************************************
class dMessageText;

class dChannelWindow : public dWindow
{   
    Q_OBJECT
    private:
        dWindowFrame *window;
        dChatApplication *application;
        
    // Пункт меню, содержит окно настроек.
        QAction *settingAct;

    // Настройки окна канала.
        dSettingChannel *settingChannel;
    
    // Разделитель.
        QSplitter *splitter;
        QMainWindow *stackedWidget;
    // Текстовый редактор с ответами.
        dMessageText *messageText;        
    // Редактор мессаги.
        QTextEdit *editorMessage;
        
    public:
    // Таблица с ответами.
        dMessageTable *messageTable;    

        dChannelWindow( dWindowFrame *_window );
        ~dChannelWindow();
        dWindowFrame *getWindowPtr() { return window; };
    
    // Устанавливает режим просмотра сообщений.
        void setViewMode( bool isTable );
        
    public slots:
    
        void addNameToEdit( const QString &_name );                    
    // Если вызвать настройки окна канала.
        void settingToggled( bool _clickable );
    
    // Добавляет сообщение из канала.
        void addMessage( dPUser _usr, const QString &_msg);
    // Добавляет сообщение типа "Me" из канала.
        void addMessageMe( dPUser _usr, const QString &_msg);
};

#endif // DCHANNELWINDOW_H
