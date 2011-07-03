#include "dsettinguserwin.h"
#include "duserwindow.h"


dSettingUserWin::dSettingUserWin( const QString &_key, dSetting *_parent, dUserWindow *_userWindow  ):
            userWindow(_userWindow),
            dSetting(_key,_parent )
{ 
    switch( toInt(tr("icon_size_to_icon"),tr("value"),0) )
    {
        case 0:  iconSizeToIcon = QSize(16,16);
        break;
        case 1:  iconSizeToIcon = QSize(24,24);
        break;
        case 2:  iconSizeToIcon = QSize(32,32);
        break;
        case 3:  iconSizeToIcon = QSize(48,48);
        break;
        case 4:  iconSizeToIcon = QSize(64,64);
        break;
    }
    switch( toInt(tr("icon_size_to_list"),tr("value"),0) )
    {
        case 0:  iconSizeToList= QSize(16,16);
        break;
        case 1:  iconSizeToList = QSize(24,24);
        break;
        case 2:  iconSizeToList = QSize(32,32);
        break;
        case 3:  iconSizeToList = QSize(48,48);
        break;
        case 4:  iconSizeToList = QSize(64,64);
        break;
    }
    switch( toInt(tr("icon_size_to_table"),tr("value"),0) )
    {
        case 0:  iconSizeToTable= QSize(16,16);
        break;
        case 1:  iconSizeToTable = QSize(24,24);
        break;
        case 2:  iconSizeToTable = QSize(32,32);
        break;
        case 3:  iconSizeToTable = QSize(48,48);
        break;
        case 4:  iconSizeToTable = QSize(64,64);
        break;
    }             
};

dSettingUserWin::~dSettingUserWin()
{
   // saveSetting();
};

QWidget *dSettingUserWin::createWidget()
{
    QWidget * widget =  new QWidget();
    
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(1);
    layout->setSpacing(5);
    
        QGridLayout *layoutGrid = new QGridLayout();
        layoutGrid->setSpacing(3);
        layoutGrid->setAlignment(Qt::AlignLeft);
        
        layoutGrid->addWidget ( new QLabel("Размер значков в режиме \"значки\": "), 0, 0 ,Qt::AlignRight);
        iconSizeToIconComboBox = new QComboBox;
        iconSizeToIconComboBox->addItem(tr("Маленькие (16x16)"),QSize(16,16));
        iconSizeToIconComboBox->addItem(tr("Побольше (24x24)"),QSize(24,24));
        iconSizeToIconComboBox->addItem(tr("Средние (32x32)"),QSize(32,32));
        iconSizeToIconComboBox->addItem(tr("Стандартные (48x48)"),QSize(48,48));
        iconSizeToIconComboBox->addItem(tr("Большие (64x64)"),QSize(64,64));
        iconSizeToIconComboBox->setCurrentIndex(toInt(tr("icon_size_to_icon"),tr("value"),2));
        connect(iconSizeToIconComboBox, SIGNAL(activated (int)), this, SLOT(sizeIconToIconActivated (int)));
        layoutGrid->addWidget( iconSizeToIconComboBox, 0, 1  );
    
        layoutGrid->addWidget( new QLabel("Размер значков в режиме \"листа\": "),1,0 ); 
        iconSizeToListComboBox = new QComboBox;
        iconSizeToListComboBox->addItem(tr("Маленькие (16x16)"),QSize(16,16));
        iconSizeToListComboBox->addItem(tr("Побольше (24x24)"),QSize(24,24));
        iconSizeToListComboBox->addItem(tr("Средние (32x32)"),QSize(32,32));
        iconSizeToListComboBox->addItem(tr("Стандартные (48x48)"),QSize(48,48));
        iconSizeToListComboBox->addItem(tr("Большие (64x64)"),QSize(64,64));
        iconSizeToListComboBox->setCurrentIndex(toInt(tr("icon_size_to_list"),tr("value"),0));
        connect(iconSizeToListComboBox, SIGNAL(activated (int)), this, SLOT(sizeIconToListActivated (int)));
        layoutGrid->addWidget (iconSizeToListComboBox,1,1 );
    
        layoutGrid->addWidget( new QLabel("Размер значков в режиме \"таблица\": "),2,0 ); 
        iconSizeToTableComboBox = new QComboBox;
        iconSizeToTableComboBox->addItem(tr("Маленькие (16x16)"),QSize(16,16));
        iconSizeToTableComboBox->addItem(tr("Побольше (24x24)"),QSize(24,24));
    //    iconSizeToTableComboBox->addItem(tr("Средние (32x32)"),QSize(32,32));
    //    iconSizeToTableComboBox->addItem(tr("Стандартные (48x48)"),QSize(48,48));
    //    iconSizeToTableComboBox->addItem(tr("Большие (64x64)"),QSize(64,64));
        iconSizeToTableComboBox->setCurrentIndex(toInt(tr("icon_size_to_table"),tr("value"),0));
        connect(iconSizeToTableComboBox, SIGNAL(activated (int)), this, SLOT(sizeIconToTableActivated (int)));
        layoutGrid->addWidget (iconSizeToTableComboBox,2,1 );
        
    layout->addItem(layoutGrid); 
    widget->setLayout(layout); 

    return widget; 
};

void dSettingUserWin::sizeIconToIconActivated( int _index )
{
    set(tr("icon_size_to_icon"),tr("value"),_index);
    iconSizeToIcon = iconSizeToIconComboBox->itemData(_index).toSize();
    if( toInt(tr("view_type"),tr("value"),0) == 1)
    {
        userWindow->userIconView->setIconSize(iconSizeToIcon);
        userWindow->searchIconView->setIconSize(iconSizeToIcon);
    }
}
void dSettingUserWin::sizeIconToListActivated( int _index )
{
    set(tr("icon_size_to_list"),tr("value"),_index);
    iconSizeToList = iconSizeToListComboBox->itemData(_index).toSize();
    if( toInt(tr("view_type"),tr("value"),0) == 2)
    {
        userWindow->userListView->setIconSize(iconSizeToList);
        userWindow->searchListView->setIconSize(iconSizeToList);
    }
}
void dSettingUserWin::sizeIconToTableActivated( int _index )
{
    set(tr("icon_size_to_table"),tr("value"),_index);
    iconSizeToTable = iconSizeToTableComboBox->itemData(_index).toSize();
    if( toInt(tr("view_type"),tr("value"),0) == 3)
    {
        userWindow->userTableView->setIconSize(iconSizeToTable);
        userWindow->searchTableView->setIconSize(iconSizeToTable);
    }
}


