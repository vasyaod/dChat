#include "../dchatapplication.h"
#include "../duserwindow.h"

#include "dmanagerex.h"
#include "duserex.h"

dManagerEx::dManagerEx( dChatApplication * _application ):
        dManager(_application)
{   
    /*ПУСТО*/    
    model = new QStandardItemModel(0, 9, this);
    model->setHeaderData(0, Qt::Horizontal, tr("Name"));
    model->setHeaderData(1, Qt::Horizontal, tr("IP"));
    model->setHeaderData(2, Qt::Horizontal, tr("Host"));
    model->setHeaderData(3, Qt::Horizontal, tr("Login"));
    model->setHeaderData(4, Qt::Horizontal, tr("Version"));
    model->setHeaderData(5, Qt::Horizontal, tr("AutoAnswer"));
    model->setHeaderData(6, Qt::Horizontal, tr("Activity"));
    model->setHeaderData(7, Qt::Horizontal, tr("Mode"));
    model->setHeaderData(8, Qt::Horizontal, tr("Sex"));
    selectionModel = new QItemSelectionModel(model);    
};

dManagerEx::~dManagerEx()
{   
    // Надо убить всех пользователей, до того, как закроем модель
    // данных.
    foreach(dPUser usr, get_users())
        usr->delete_user();
    
    delete selectionModel;
    delete model;
};
void dManagerEx::deleteUser( dUser * _user )
{
    emit signal_delete_user( _user->get_pointer() ); 
    emit signal_count_user_change( this->get_user_count()-1); 
    dManager::deleteUser(_user);
}

dUser *dManagerEx::addUser(dUser * _user)
{
    dUser * _user_out = dManager::addUser(_user);
    emit signal_count_user_change( this->get_user_count());
    emit signal_add_user( _user->get_pointer() );
	return _user_out;
}

//////////////////////////////////////////////////////////////
// Возвращает пользователя который является текущим в модели.
dPUser dManagerEx::getCurrentUserToModel( /* QModelIndex &_index*/ )
{
    QItemSelectionModel *selectionModel = get_selectionModel();
    QAbstractItemModel *model = get_model();

    QModelIndex index = selectionModel->currentIndex();

    return model->data(model->index(index.row(),0),Qt::UserRole).value<dPUser>();
};

//////////////////////////////////////////////////////////////
// Возвращает список пользователей которые выделены в модели.
QList<dPUser> dManagerEx::getSelectedUserToModel()
{
    QList<dPUser> users;
    
    QItemSelectionModel *selectionModel = get_selectionModel();
    QAbstractItemModel *model = get_model();

    QModelIndexList indexList = selectionModel->selectedIndexes();
    foreach(QModelIndex index, indexList )
    {
        if( index.column() == 0 )
            users.push_back(model->data(model->index(index.row(),0),Qt::UserRole).value<dPUser>());
    }
    return users;
};
