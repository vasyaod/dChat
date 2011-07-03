#include "dsettingplugin.h"
#include "dplugininterface.h"
#include "dchatapplication.h"

dSettingPlugin::dSettingPlugin( const QString &_key, dSetting *_parent ):
            dSetting(_key,_parent )
{ 
    application = qobject_cast<dChatApplication*>(QApplication::instance());
};

dSettingPlugin::~dSettingPlugin()
{
// saveSetting();
};

QWidget *dSettingPlugin::createWidget()
{
    QWidget * widget =  new QWidget();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(1);
    layout->setSpacing(5);
    
    QTableWidget *pluginsTable = new QTableWidget();
    pluginsTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    pluginsTable->setSelectionBehavior( QAbstractItemView::SelectRows );
    pluginsTable->horizontalHeader()->setHighlightSections(false);
    pluginsTable->setEditTriggers(false);        
    pluginsTable->setColumnCount(2);
    QStringList labels;
    labels << tr("Ключ") << tr("Описание");
    pluginsTable->setHorizontalHeaderLabels(labels);
    pluginsTable->verticalHeader()->hide();
    pluginsTable->horizontalHeader()->setStretchLastSection( true );
    pluginsTable->setSelectionMode(QAbstractItemView::SingleSelection);

    int i = 0;
    foreach( dChatPluginInterface* pluginInterface,application->getPluginsList()) 
    {
        pluginsTable->setRowCount(i+1);
        QTableWidgetItem *item0 = new QTableWidgetItem(pluginInterface->key());
        pluginsTable->setItem(i,0,item0);           
        QTableWidgetItem *item1 = new QTableWidgetItem(pluginInterface->title());
        pluginsTable->setItem(i,1,item1);           
        i++;
    }
    
    layout->addWidget(pluginsTable);
    layout->addStretch ( 1 );
        
    widget->setLayout(layout); 
    return widget; 
};


