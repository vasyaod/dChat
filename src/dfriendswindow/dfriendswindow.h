#ifndef DFRIENDSWINDOW_H
#define DFRIENDSWINDOW_H

#include <QtGui>

#include "../dwindow.h"


// Структура описывающая друга.
class dFriend
{
    public:
        bool operator== (dFriend &_friend);
        QString name;
        QString ip;
};
#include "dfriendview.h"        // <<<<<<<<<<<------- DFRIENDVIEW_H

class dChatApplication;
class dSetting;

class dFriendsWindow : public dWindow
{   
    Q_OBJECT
    private:
        dWindowFrame *window;
        dChatApplication *application;
    // Указатель на настройки.
        dSetting *settingFriend;
    // Указатель на виджет списка юзеров.
        dFriendView<QListView> *friensList;
    // Cписок друзей.
        QList<dFriend> friends;
        
    public:
        dFriendsWindow( dWindowFrame *_window, QObject *_parent = 0);
        ~dFriendsWindow();
        
    // Возвращает ссылку на список друзей.
        QList<dFriend> &get_friends(){ return friends; };
    // Добавляет в список друзей.
        bool addFriend( const QString &_name, const QString &_ip );
    // Удаление друзей.
        bool deleteFriend( const QString &_name, const QString &_ip );
        void refreshFriendsList();
    
    public slots:
    // Добавляет в список друзей.
        void addFriendNameAndIP();
        void addFriendName();
        void addFriendIP();
    // Удаление друзей.
        void deleteFriend();
    // При двойном счелчке мыши в листе пользователей.
        void itemDoubleClicked ( const QModelIndex & index );
    // Устанавливает новый заголовок.
  //      void setTopic( const QString &_topic );

};

#endif // DFRIENDSWINDOW_H


