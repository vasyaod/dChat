#ifndef DTOPICWINDOW_H
#define DTOPICWINDOW_H

#include <QtGui>

#include "../dwindow.h"

class dChatApplication;
class dSetting;

class dTopicWindow : public dWindow
{   
    Q_OBJECT
    private:
        dWindowFrame *window;
        dChatApplication *application;
    public:
    // Редактор заголовка.
        QTextEdit *topicEditor;

        dTopicWindow( dWindowFrame *_window, QObject *_parent = 0);
        ~dTopicWindow();
        dWindowFrame *getWindowPtr() { return window; };

    public slots:
    
    // Устанавливает новый заголовок.
        void setTopic( const QString &_topic );

};

// Изменим немного класс QTextEdit, так как нам надо отлавливать нажатие
// клавиши eNTER.
class dTopicTextEditEx : public QTextEdit
{
    Q_OBJECT
    private:
        dChatApplication *application;    
    // Виджет с редактором заголовка.
        QWidget *topicEditor; 
    // Текстовое поле редактора заголовка.
        QTextEdit *topicEditorTextEdit;
    public:
        dTopicTextEditEx(  QWidget *_parent=0);
    protected:
        virtual void keyPressEvent ( QKeyEvent * _event );
    // Тут включается редактор.. при двойном нажатии мыши.
        virtual void mouseDoubleClickEvent ( QMouseEvent * _event );
    // Метод отсылает новый топик.
        void send( QString new_topic );

    public slots:
    // Кнопка редактора заголовка, которая устанавливет новый топик.
        void clickedSendButton();
};

#endif // DTOPICWINDOW_H
