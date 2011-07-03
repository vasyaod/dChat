#ifndef DMESSAGEEDITOR_H
#define DMESSAGEEDITOR_H

#include <QtGui>
#include "../net/duser.h"

class dSetting;
class dChatApplication;
class dSettingMessageEditor;

class dMessageEditor: public QMainWindow
{   
    Q_OBJECT
    private:

    QAction *actionSave,
            *actionTextBold,
            *actionTextUnderline,
            *actionTextItalic,
            *actionTextColor,
            *actionAlignLeft,
            *actionAlignCenter,
            *actionAlignRight,
            *actionAlignJustify,
            *actionUndo,
            *actionRedo,
            *actionCut,
            *actionCopy,
            *actionPaste;

    QComboBox   *comboStyle,
                *comboFont,
                *comboSize;

    // Хранит старое сообщение.
        QString oldMsg;
    // Указаель на обьект приложения.
        dChatApplication *application;
    // Указатель на настройки редактора.
        dSettingMessageEditor * settingMessageEditor;
    // Сплидер - разделитель......
        QSplitter *splitter;
    // Список пользователей, для кого преднозначено данное сообщение.
        QList<dPUser> to;
    // Пользователь, от чьего имени будет отправлено данное сообщение.
        dPUser from;
    // Редактор где содержиться старое сообщение.
        QTextEdit *oldMessageTextEdit;        
    // Редактор нового сообщения.
        QTextEdit *newMessageTextEdit;       
    // Содержит вид нужного сообщения.
        QComboBox *typeComboBox;
    // Активное окно перед тем как открылся редактор сообщений...
        QWidget * activeWindow;
    // Флаг, если он включен,то окно нужно показать на экране.
    // если выключен, то окно свернуто в таск бар..
        bool showed;
    public:
        enum typeMessage {
            msg_personal  = 0x1,
            msg_mass = 0x2,
        };

    ///////////////////////// КОНСТРУКТОР /////////////////////////////////////
    // _from - кто собирается отправить.
    // _to - куда собираются отправить.
    // _msg - текст предыдущего сообщения.
        dMessageEditor( dSettingMessageEditor *_settingMessageEditor,
                        QList<dPUser> _to, 
                        dPUser _from, 
                        const QString &_msg,
                        const QString &_title,
                        typeMessage tm,
                        bool _showed = true,
                        bool _html=false,
                        QWidget *_parent = 0);
        ~dMessageEditor();
    
    protected:
    // Перегружаем событие на закрытие.
        virtual void closeEvent ( QCloseEvent * _event );
    // Перегружаем событие на нажатие клавиши, дабы отловить нажатие CNTL+ENTER
        virtual void keyPressEvent ( QKeyEvent * _event );    
    // Че придется!!!
        bool event ( QEvent * _event );
    public slots:
    // Вызывается при нажатии клавиши "Отправить"....
        void clickedSendButton();
    // Слот, реакция на перемещение сплитера.
        void splitterMoved( int pos, int index );
        
        void textBold();
        void textUnderline();
        void textItalic();
        void textAlign(QAction *);

        void textFamily(const QString &f);
        void textSize(const QString &p);
        
        void textColor();
        void saveMessage();
//    protected slots:
};
#endif // DMESSAGEEDITOR_H
