#ifndef DSETTINGUSERS_H
#define DSETTINGUSERS_H

#include <QtGui>
#include <QtXml>

#include "../dsetting.h"
#include "../net/duser.h"

class dChatApplication;

class dSettingUsers: public dSetting
{
    Q_OBJECT
    private:
        dChatApplication *application;
    
    // Таблица с типами пользователей.
        QTableWidget *typeTable;
    // Таблица с уже созданными пользователями.
        QTableWidget *userTable;
    // Список указателей на действующих локальных пользователей.    
        QList<dPUser> user_list;
    public:
    
        dSettingUsers( dSetting *_parent );
//        ~dSettingUsers();
        virtual QWidget *createWidget();
    
    public slots:
    // При нажатии кнопки добавления пользователя.
        void clickedAddButton ( bool checked );
    // При нажатии кнопки удаления пользователя.
        void clickedDeleteButton ( bool checked );
    // При двойном нажатии на пользователе в таблице.
        void userDoubleClicked ( const QModelIndex & index );

};

#endif // DSETTINGUSERS_H

