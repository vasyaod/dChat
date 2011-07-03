#include "dsettingchannel.h"
#include "dchannelwindow.h"
#include "dmessagetable.h"

dSettingChannel::dSettingChannel( const QString &_key, dSetting *_parent, dChannelWindow *_channelWindow  ):
            channelWindow(_channelWindow),
            dSetting(_key,_parent )
{ 
    
};

dSettingChannel::~dSettingChannel()
{
   // saveSetting();
};

QWidget *dSettingChannel::createWidget()
{
    QWidget * widget =  new QWidget();
    
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(1);
    layout->setSpacing(5);
    
    layout->addWidget( new QLabel("Вид списка сообщений:") ); 
    QHBoxLayout *viewTypeLayout = new QHBoxLayout;
 //   viewTypeLayout->setSpacing(5);
        viewTypeComboBox = new QComboBox;
        viewTypeComboBox->addItem(tr("Таблица"));
        viewTypeComboBox->addItem(tr("Текстовый редактор"));
        viewTypeComboBox->setCurrentIndex(toInt(tr("view_type"),tr("value"),0));
        connect(viewTypeComboBox, SIGNAL(activated (int)), this, SLOT(viewTypeActivated (int)));
        viewTypeLayout->addWidget (viewTypeComboBox );
        viewTypeLayout->addStretch ( 1 );            
    layout->addItem( viewTypeLayout );
    
        QHBoxLayout *messageMaxLayout = new QHBoxLayout;
        messageMaxLayout->setSpacing(5);
        messageMaxLayout->addWidget( new QLabel("Максимальное число строк(сообщений) в таблице:") ); 
        messageMaxSpinBox = new QSpinBox;
        messageMaxSpinBox->setSingleStep(1);
        messageMaxSpinBox->setMinimum(1);
        messageMaxSpinBox->setEnabled ( !viewTypeComboBox->currentIndex() );
        messageMaxSpinBox->setValue(toInt(tr("max_message"),tr("value"),30));

        connect(messageMaxSpinBox, SIGNAL(valueChanged(int)), this, SLOT(messageMaxChanged(int)));
        messageMaxLayout->addWidget( messageMaxSpinBox );
        messageMaxLayout->addStretch ( 5 );       
    layout->addItem( messageMaxLayout );

        QHBoxLayout *nameMaxLayout = new QHBoxLayout;
        nameMaxLayout->setSpacing(5);
        nameMaxLayout->addWidget( new QLabel("Максимальный размер имени пользователя в табличном режиме:") ); 
        nameMaxSpinBox = new QSpinBox;
        nameMaxSpinBox->setSingleStep(1);
        nameMaxSpinBox->setMinimum(8);
        nameMaxSpinBox->setEnabled ( !viewTypeComboBox->currentIndex() );
        nameMaxSpinBox->setValue(toInt(tr("max_name"),tr("value"),10));
        connect(nameMaxSpinBox, SIGNAL(valueChanged(int)), this, SLOT(nameMaxChanged(int)));
        nameMaxLayout->addWidget( nameMaxSpinBox );
        nameMaxLayout->addStretch ( 5 );       
    
    layout->addItem( nameMaxLayout );
    
    widget->setLayout(layout); 

    return widget; 
};

void dSettingChannel::viewTypeActivated( int _index )
{
    if( toInt(tr("view_type"),tr("value"),0) != _index )
    {
        set(tr("view_type"),tr("value"),_index);
        channelWindow->setViewMode(!_index);

    }
    nameMaxSpinBox->setEnabled ( !_index );
    messageMaxSpinBox->setEnabled ( !_index );
}

bool dSettingChannel::isTableView()
{
    return !toInt(tr("view_type"),tr("value"),0);
}

void dSettingChannel::messageMaxChanged( int _value )
{
    channelWindow->messageTable->setMaximumMessage(_value);
    set(tr("max_message"),tr("value"),_value);
}

void dSettingChannel::nameMaxChanged( int _value )
{
    channelWindow->messageTable->setMaximumName(_value);
    set(tr("max_name"),tr("value"),_value);
}

