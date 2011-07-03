#include "dsettingfriends.h"
#include "dfriendswindow.h"

dSettingFriends::dSettingFriends(   const QString &_key,
                                    dSetting *_parent,
                                    dFriendsWindow *_friendsWindow ):
            friendsWindow(_friendsWindow),
            dSetting(_key,_parent )
{ 
    friends = &friendsWindow->get_friends();
};

dSettingFriends::~dSettingFriends()
{
   // saveSetting();
};

QWidget *dSettingFriends::createWidget()
{
    QWidget * widget =  new QWidget();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(1);
    layout->setSpacing(5);
    layout->addWidget(new QLabel(tr("<b>Список занесенных в \"Друзья\":</b>")));   

        QHBoxLayout *layoutFriends = new QHBoxLayout;
        layoutFriends->setSpacing(5);
        friendsTable = new QTableWidget();
        friendsTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        friendsTable->setSelectionBehavior( QAbstractItemView::SelectRows );
        friendsTable->horizontalHeader()->setHighlightSections(false);
        friendsTable->setEditTriggers(false);        
        friendsTable->setColumnCount(2);
        QStringList labels;
        labels << tr("Имя") << tr("IP");
        friendsTable->setHorizontalHeaderLabels(labels);
        friendsTable->verticalHeader()->hide();
        friendsTable->horizontalHeader()->setStretchLastSection( true ); 
        friendsTable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
        friendsTable->setSelectionMode(QAbstractItemView::SingleSelection);
        friendsTable->setRowCount( (*friends).size() );

        for (int i = 0; i < (*friends).size() ; ++i)
        {
            QTableWidgetItem *item0 = new QTableWidgetItem((*friends)[i].name.isEmpty()? tr("*"):(*friends)[i].name);
            friendsTable->setItem(i,0,item0);
            QTableWidgetItem *item1 = new QTableWidgetItem((*friends)[i].ip.isEmpty()? tr("*"):(*friends)[i].ip);
            friendsTable->setItem(i,1,item1);           
        }
        layoutFriends->addWidget (friendsTable );
            QVBoxLayout *deleteLayout = new QVBoxLayout;
            deleteLayout->setMargin(1);
            QPushButton * deleteButton = new QPushButton(tr("Удалить"));
      //      deleteButton->setIcon(QIcon(tr("pic/open32x32.png")));
            deleteLayout->addWidget( deleteButton );   
            connect(deleteButton, SIGNAL(clicked()), this, SLOT(clickedDeleteButton()));
            deleteLayout->addStretch();
        layoutFriends->addItem( deleteLayout );   
        layoutFriends->addStretch ( 1 );
    layout->addItem(layoutFriends);
    widget->setLayout(layout); 
    return widget; 
};

void dSettingFriends::clickedDeleteButton()
{
    if ( friendsTable->currentRow() != -1)
    {
        int currentRow = friendsTable->currentRow();
        QString name = friendsTable->item(currentRow,0)->text();
        QString ip = friendsTable->item(currentRow,1)->text();
        friendsTable->removeRow(currentRow);
        friendsWindow->deleteFriend(name,ip);
        friendsWindow->refreshFriendsList();
    }
}


