#include "dsettingusers.h"
#include "dmanagerex.h"
#include "dlocaluserex.h"
#include "../dchatapplication.h"

dSettingUsers::dSettingUsers( dSetting *_parent ):
            dSetting(tr("users"),_parent )
{ 
    dPUser usr;

    application = qobject_cast<dChatApplication*>(QApplication::instance());

    QDomElement element = getXmlElement();
    QDomElement userElement = element.firstChildElement();
    while (!userElement.isNull()) {
        if (userElement.tagName() == "user" ) {
            QString key = userElement.attribute(tr("key"));
            if( application->usersFactory.contains(key) )
            {
                usr = application->usersFactory.create(key,
                                    application->get_managerEx(),
                                    userElement.attribute(tr("name")),
                                    userElement,this);
                user_list.push_back(usr);
            }
        }
        userElement = userElement.nextSiblingElement();
    }
};

QWidget *dSettingUsers::createWidget()
{ 
    QWidget * widget =  new QWidget();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(1);
    layout->setSpacing(5);
    
    layout->addWidget( new QLabel(tr("В dChat существует возможность добавить нескольких пользователей различных типов:")) );   

        typeTable = new QTableWidget();
        typeTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        typeTable->setSelectionBehavior( QAbstractItemView::SelectRows );
        typeTable->horizontalHeader()->setHighlightSections(false);
        typeTable->setEditTriggers(false);        
        typeTable->setColumnCount(3);
        QStringList labels;
        labels << tr("Тип/Ключ") << tr("Название") << tr("Описание");
        typeTable->setHorizontalHeaderLabels(labels);
        typeTable->verticalHeader()->hide();
        typeTable->horizontalHeader()->setStretchLastSection( true );
        typeTable->setSelectionMode(QAbstractItemView::SingleSelection);
//        typeTable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
        
        QList<QString> keys = application->usersFactory.keys();
        typeTable->setRowCount( keys.size() );
        for (int i = keys.size()-1; i >= 0 ; --i) {
            QTableWidgetItem *item0 = new QTableWidgetItem(keys[i]);
            typeTable->setItem(i,0,item0);           
            QTableWidgetItem *item1 = new QTableWidgetItem(application->usersFactory.title(keys[i]));
            typeTable->setItem(i,1,item1);           
            QTableWidgetItem *item2 = new QTableWidgetItem(application->usersFactory.description(keys[i]));
            typeTable->setItem(i,2,item2);           
        }
        typeTable->setCurrentItem(typeTable->item(0,0));

        QHBoxLayout *typeUserLayout = new QHBoxLayout;
        typeUserLayout->setSpacing(3);
        typeUserLayout->addWidget( typeTable );   

            QVBoxLayout *addLayout = new QVBoxLayout;
            addLayout->setMargin(1);
            QPushButton * addButton = new QPushButton(tr("Добавить"));
            addButton->setIcon(QIcon(tr("pic/open32x32.png")));
            addLayout->addWidget( addButton );   
            connect(addButton, SIGNAL(clicked(bool)), this, SLOT(clickedAddButton(bool)));
            addLayout->addStretch();
        typeUserLayout->addItem( addLayout );   
    
    layout->addItem( typeUserLayout );       
    
        userTable = new QTableWidget();
        userTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        userTable->setSelectionBehavior( QAbstractItemView::SelectRows );
        userTable->horizontalHeader()->setHighlightSections(false);
        userTable->setEditTriggers(false);        
        userTable->setColumnCount(2);
        QStringList labels1;
        labels1 << tr("Имя") << tr("Тип");
        userTable->setHorizontalHeaderLabels(labels1);
        userTable->verticalHeader()->hide();
        userTable->horizontalHeader()->setStretchLastSection( true ); 
        userTable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
        userTable->setSelectionMode(QAbstractItemView::SingleSelection);
        userTable->setRowCount( user_list.size() );
  
  // Выведем список всех созданых локальных пользователей.     
        for (int i = 0; i < user_list.size() ; ++i) {
            QTableWidgetItem *item0 = new QTableWidgetItem(user_list[i]->get_name());
            item0->setIcon(QIcon(user_list[i]->get_avatar()));
            item0->setData(Qt::UserRole,QVariant::fromValue(user_list[i]));
            userTable->setItem(i,0,item0);
            QTableWidgetItem *item1 = new QTableWidgetItem(application->usersFactory.title(user_list[i]->get_type()));
            userTable->setItem(i,1,item1);           
        }
        userTable->setCurrentItem(userTable->item(0,0));
                
        QHBoxLayout *userLayout = new QHBoxLayout;
        userLayout->setSpacing(3);
        userLayout->addWidget( userTable );    
               
            QVBoxLayout *deleteLayout = new QVBoxLayout;
            deleteLayout->setMargin(1);
            QPushButton * deleteButton = new QPushButton(tr("Удалить"));
            deleteButton->setIcon(QIcon(tr("pic/open32x32.png")));
            deleteLayout->addWidget( deleteButton );   
            connect(deleteButton, SIGNAL(clicked(bool)), this, SLOT(clickedDeleteButton(bool)));
            deleteLayout->addStretch();

        userLayout->addItem( deleteLayout );   
    layout->addItem( userLayout );       
    widget->setLayout(layout); 
    return widget; 
};

void dSettingUsers::clickedAddButton ( bool checked )
{
  //  QWidget * widget =  new QWidget(this);
    QString name = QInputDialog::getText(0,tr("Новый пользователь."),tr("Введите имя нового пользователя:"));
    if( name == tr("") )
        QMessageBox::warning (0, tr("Замечание."),
                                 tr("Имя не может быть пустым."),QMessageBox::Ok,0,0);            
    else if( !application->get_managerEx()->find_user(application->get_managerEx()->get_localAddress(),name) )
    {
        QString key = typeTable->item( typeTable->currentRow(),0 )->text();
        QDomElement userElement = element.ownerDocument().createElement(tr("user"));
        element.appendChild(userElement);
        userElement.setAttribute(tr("key"),key);
        userElement.setAttribute(tr("name"),name);
        dPUser usr = application->usersFactory.create( key, application->get_managerEx(),
                                                              name, userElement,this);

        user_list.push_back(usr);
        
        userTable->setRowCount( user_list.size() );
        QTableWidgetItem *item0 = new QTableWidgetItem(usr->get_name());
        item0->setIcon(QIcon(usr->get_avatar()));
        item0->setData(Qt::UserRole,QVariant::fromValue(usr));
        userTable->setItem(user_list.size()-1,0,item0);
        QTableWidgetItem *item1 = new QTableWidgetItem(application->usersFactory.title(usr->get_type()));
        userTable->setItem(user_list.size()-1,1,item1);           
        reParsing();
    }
    else
    {
        QMessageBox::warning (0, tr("Замечание."),
                                 tr("Пользователь с таким именем уже добавлен.<br>Попытайтесь еще раз."),QMessageBox::Ok,0,0);        
    }
}

void dSettingUsers::clickedDeleteButton ( bool checked )
{
    if( user_list.size() == 1 )
    {
        QMessageBox::warning (0, tr("Замечание."),
                                 tr("Нельзя удалить всех пользователей. Должен остаться хотя бы один."),QMessageBox::Ok,0,0);        
    
        return;
    }
    QTableWidgetItem *item = userTable->item(userTable->currentRow(),0);
    dPUser usr = item->data(Qt::UserRole).value<dPUser>();
    QString name = usr->get_name();
    userTable->removeRow ( userTable->currentRow() );
    userTable->setCurrentItem(userTable->item(0,0));
    user_list.removeAll(usr);
    usr->delete_user();  
  
  // Удалим настройки из XML...  
    QDomElement element = getXmlElement();
    QDomElement userElement = element.firstChildElement();
    while (!userElement.isNull()) {
        if (userElement.tagName() == "user" && userElement.attribute(tr("name")) == name) {
            element.removeChild(userElement);
        }
        userElement = userElement.nextSiblingElement();
    }
    reParsing();
}

void dSettingUsers::userDoubleClicked ( const QModelIndex & index )
{

}
