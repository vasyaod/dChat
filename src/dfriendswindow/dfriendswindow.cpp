#include "dfriendswindow.h"
#include "dsettingfriends.h"

#include "../dchatapplication.h"
#include "../dsettinggeneral.h"

#include "../dwindowframe/dwindowframe.h"
#include "../netex/dmanagerex.h"
#include "../net/duser.h"


bool dFriend::operator== (dFriend &_friend)
{
	if( _friend.name == name && _friend.ip == ip)
		return true;
	if( _friend.name == name && ( ip == QObject::tr("*") || _friend.ip == QObject::tr("*")) )
		 return true;
	if( ( name == QObject::tr("*") || _friend.name == QObject::tr("*") )&& _friend.ip == ip)
		 return true;
	return false;
}

dFriendsWindow::dFriendsWindow( dWindowFrame *_window, QObject *_parent ):
        dWindow(tr("friends_window"),_window),
        window(_window)
{
    setTitle(tr("Друзья"));
    setIcon(QIcon(tr("pic/man64x64.png")));
    getSettingWindow()->setTitle(tr("Настройки стиля окна \"Друзья\"."));
    getWindowAct()->setShortcut(tr("Ctrl+F"));
    
    application = qobject_cast<dChatApplication*>(QApplication::instance());
    setParent(application);

    window->setMinButton(false);        // Уберем кнопочку "свернуть".    
    
    settingFriend = new dSettingFriends(tr("friends_window"),application->settingGeneral,this);
    settingFriend->setTitle(tr("Друзья"));
    settingFriend->setIcon(QIcon(tr("pic/man64x64.png")));

 //   QListView *friensList = new QListView();
    friensList = new dFriendView<QListView>(&friends,window);
    friensList->setContextMenuPolicy(Qt::ActionsContextMenu);
    friensList->setViewMode( QListView::ListMode);
    friensList->setModel(application->get_managerEx()->get_model());
    friensList->setSelectionMode(QAbstractItemView::ExtendedSelection);
    friensList->setSelectionModel(application->get_managerEx()->get_selectionModel());
    friensList->setEditTriggers(false);
   // friensList->setFlow(QListView::LeftToRight);
   // friensList->setLayoutMode( QListView::Batched );
    friensList->setWrapping(true);
    connect(friensList, SIGNAL(doubleClicked ( const QModelIndex&)), this, SLOT(itemDoubleClicked( const QModelIndex&)));

    QAction *addFriendNameAndIPAct = new QAction(tr("Добавить в друзья(nick и ip)"), this);
    addFriendNameAndIPAct->setIcon(QIcon(tr("pic/man64x64.png")));
    connect(addFriendNameAndIPAct, SIGNAL(triggered()), this, SLOT(addFriendNameAndIP()));
    application->contextUserMenu.addAction(addFriendNameAndIPAct);

    QAction *addFriendNameAct = new QAction(tr("Добавить в друзья(nick)"), this);
    addFriendNameAct->setIcon(QIcon(tr("pic/man64x64.png")));
    connect(addFriendNameAct, SIGNAL(triggered()), this, SLOT(addFriendName()));
    application->contextUserMenu.addAction(addFriendNameAct);

    QAction *addFriendIPAct = new QAction(tr("Добавить в друзья(ip)"), this);
    addFriendIPAct->setIcon(QIcon(tr("pic/man64x64.png")));
    connect(addFriendIPAct, SIGNAL(triggered()), this, SLOT(addFriendIP()));
    application->contextUserMenu.addAction(addFriendIPAct);

    QAction *deleteFriendAct = new QAction(tr("Удалить из друзей"), this);
    deleteFriendAct->setIcon(QIcon(tr("pic/man64x64.png")));
    connect(deleteFriendAct, SIGNAL(triggered()), this, SLOT(deleteFriend()));
    application->contextUserMenu.addAction(deleteFriendAct);

    // Добавим в этот виджет контекстное меню....
    application->contextUserMenu.addWidget(friensList);

    window->setCentralWidget(friensList);
    connect(window, SIGNAL(closed()), this, SLOT(hide()));
    
    // Запольни список друзей из файла настройки.
    QDomElement element = settingFriend->getXmlElement();
    QDomElement friendElement = element.firstChildElement();
    dFriend _friend;
    while (!friendElement.isNull()) {
        if (friendElement.tagName() == tr("friend") )
        { 
            _friend.name = friendElement.attribute(tr("name"));
            _friend.ip = friendElement.attribute(tr("ip"));
            friends << _friend;
        }
        friendElement = friendElement.nextSiblingElement();
    }
}

dFriendsWindow::~dFriendsWindow()
{

};

bool dFriendsWindow::addFriend( const QString &_name, const QString &_ip )
{
    dFriend _friend;
    _friend.name = _name;
    _friend.ip = _ip;

    foreach(dFriend frd, friends)
        if( frd == _friend )
            return false;

    QDomElement element = settingFriend->getXmlElement();
    QDomElement friendElement = element.ownerDocument().createElement("friend");
    element.appendChild(friendElement);
    friendElement.setAttribute(tr("name"),_name);
    friendElement.setAttribute(tr("ip"),_ip);

    friends << _friend;    
    return true;
};

bool dFriendsWindow::deleteFriend( const QString &_name, const QString &_ip )
{
    dFriend _friend;
    _friend.name = _name;
    _friend.ip = _ip;

    QList<dFriend> friends_temp = friends;
    friends.clear();
    foreach(dFriend frd, friends_temp)
        if( !( frd.name ==_name && frd.ip ==_ip ) )
            friends << frd;
        

    QDomElement element = settingFriend->getXmlElement();
    QDomElement friendElement = element.firstChildElement();
    while (!friendElement.isNull()) {
        if( friendElement.tagName() == tr("friend") &&
            ( friendElement.attribute(tr("name"))==_name && friendElement.attribute(tr("ip"))==_ip) )            
        { 
            element.removeChild(friendElement);
        }
        friendElement = friendElement.nextSiblingElement();
    }
  
    return true;
};

void dFriendsWindow::deleteFriend()
{
    QAbstractItemModel *model = application->get_managerEx()->get_model();
    QItemSelectionModel *selectionModel = application->get_managerEx()->get_selectionModel();
    QModelIndexList indexList = selectionModel->selectedIndexes();

    foreach(QModelIndex index, indexList)
    {
//        friensList->setRowHidden(index.row(),true);
        QString name = model->data(model->index(index.row(),0)).toString(); 
        QString ip = model->data(model->index(index.row(),1)).toString(); 
        deleteFriend(name,ip);
        deleteFriend(name,tr("*"));
        deleteFriend(tr("*"),ip);
    }
    refreshFriendsList();
}

void dFriendsWindow::addFriendNameAndIP()
{
    QAbstractItemModel *model = application->get_managerEx()->get_model();
    QItemSelectionModel *selectionModel = application->get_managerEx()->get_selectionModel();
    QModelIndexList indexList = selectionModel->selectedIndexes();

    foreach(QModelIndex index, indexList)
    {
        QString name = model->data(model->index(index.row(),0)).toString(); 
        QString ip = model->data(model->index(index.row(),1)).toString(); 
        addFriend(name,ip);
    }
    refreshFriendsList();
};

void dFriendsWindow::addFriendName()
{
    QAbstractItemModel *model = application->get_managerEx()->get_model();
    QItemSelectionModel *selectionModel = application->get_managerEx()->get_selectionModel();
    QModelIndexList indexList = selectionModel->selectedIndexes();

    foreach(QModelIndex index, indexList)
    {
        QString name = model->data(model->index(index.row(),0)).toString(); 
        QString ip = model->data(model->index(index.row(),1)).toString(); 
        addFriend(name,tr("*"));
    }
    refreshFriendsList();
};
void dFriendsWindow::addFriendIP()
{
    QAbstractItemModel *model = application->get_managerEx()->get_model();
    QItemSelectionModel *selectionModel = application->get_managerEx()->get_selectionModel();
    QModelIndexList indexList = selectionModel->selectedIndexes();

    foreach(QModelIndex index, indexList)
    {
//        friensList->setRowHidden(index.row(),false);
        QString name = model->data(model->index(index.row(),0)).toString(); 
        QString ip = model->data(model->index(index.row(),1)).toString(); 
        addFriend(tr("*"),ip);
    }
    refreshFriendsList();
};

void dFriendsWindow::refreshFriendsList()
{
    QAbstractItemModel *model = application->get_managerEx()->get_model();

    for (int i = 0; i < model->rowCount() ; ++i)
    {
        dFriend _friend;
        _friend.name = model->data(model->index(i,0)).toString(); 
        _friend.ip = model->data(model->index(i,1)).toString(); 
        friensList->setRowHidden(i,true);
        foreach(dFriend frd, friends)
            if( frd == _friend )
                friensList->setRowHidden(i,false);
    }
};

void dFriendsWindow::itemDoubleClicked ( const QModelIndex & index )
{
    dManagerEx *manager = application->get_managerEx();
    application->createMessageEditor( application->get_managerEx()->getSelectedUserToModel(),manager->get_main_user(),tr(""),tr("Новое сообщение."));    
}

/*
void dTopicWindow::setTopic( const QString &_topic )
{
    topicEditor->setPlainText(_topic);
}
*/
