#ifndef DSETTINGFRIENDS_H
#define DSETTINGFRIENDS_H

#include <QtGui>
#include "../dsetting.h"

class dFriend;
class dFriendsWindow;

class dSettingFriends: public dSetting
{
    Q_OBJECT
    private:
    // Указатель на список друзей.
        QList<dFriend> *friends;
    // Таблица со всеми друзьями.
        QTableWidget *friendsTable;
    // Указ. на окно друзей.
        dFriendsWindow *friendsWindow;
    public:
        dSettingFriends( const QString &_key, dSetting *_parent, dFriendsWindow *_friendsWindow );
        ~dSettingFriends();

        virtual QWidget *createWidget();
    
    public slots:
        // Вызывается при нажатии кнопки удаления друга....
        void clickedDeleteButton();
};

#endif // DSETTINGFRIENDS_H

