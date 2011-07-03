#ifndef DUSERINFOWINDOW_H
#define DUSERINFOWINDOW_H

#include <QtGui>

class dPUser;
class dChatApplication;

class dUserInfoWindow: public QWidget
{   
 //   Q_OBJECT
    public:
    // Указаель на обьект приложения.
    //    dChatApplication *application;

    // Поле с теекстом авто ответа.
    //    QTextEdit * auto_answer;        

        dUserInfoWindow( dPUser usr,QWidget *_parent = 0);
//        ~dMessageEditor();
    
    protected:
    // Перегружаем событие на закрытие.
        virtual void closeEvent ( QCloseEvent * _event );
};
#endif // DUSERINFOWINDOW_H
