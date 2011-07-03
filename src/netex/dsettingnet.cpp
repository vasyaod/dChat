#include "dsettingnet.h"
#include "dmanagerex.h"
#include "diplistex.h"

#include "../dchatapplication.h"
#include "../net/dservice.h"


dSettingNet::dSettingNet( dSetting *_parent ):
            dSetting(tr("nets"),_parent )
{ 
    application = qobject_cast<dChatApplication*>(QApplication::instance());
    
// Так как следующий код платформо зависим, то используем
// операторы компилятора. 
#ifdef Q_WS_WIN
    uint networkModule = toInt(tr("network_module"),tr("value"),0);
#else
    uint networkModule = 0;
#endif
    try // Перехватим исключение....
    {
        dchat = new dService(application->get_managerEx(),toInt(tr("port"),tr("value"),8167),networkModule);
        dchat->onLog(stdout, 0 );	// Выведем лог в стандартный поток.
        QHostAddress broadcast_ip;
        broadcast_ip.setAddress(get(tr("broadcast_ip"),tr("value"),tr("1.2.3.255")));
        //dchat->set_broadcast_ip(broadcast_ip);
        application->get_managerEx()->set_timeout(toInt(tr("timeout"),tr("value"),150));
        application->get_managerEx()->set_interval_refresh(toInt(tr("refresh"),tr("value"),60));
        application->get_managerEx()->set_interval_ping(toInt(tr("refresh_info"),tr("value"),80));
        if( toInt(tr("send_type"),tr("value"),1) == 0)
            dchat->set_send_type(dService::broadcast_ip_type);
        else
            dchat->set_send_type(dService::list_ip_type);
    }
    catch( dService::dServiceError error )
    {
        if( error == dService::load_plugin )
            QMessageBox::critical(0, tr("Error."),
                                     tr("Не могу загрузить сетевую библиотеку dUdpSocket.dll"),QMessageBox::Ok,0,0);
        if( error == dService::init )
            QMessageBox::critical(0, tr("Error."),
                                     tr("Не могу инициализировать сокет. Возможно, на этом порту\n висят другие программы. Выключите их и зайдите\n Настройки->Сетивые->Применить."),QMessageBox::Ok,0,0);
        dchat = 0;
    }
    catch(...)
    {
        QMessageBox::critical(0, tr("Error."),
                                 tr("Ошибка при инициализации сети."),QMessageBox::Ok,0,0);
        dchat = 0;
    }
    
   // new dRangeIP(QHostAddress(tr("1.2.2.231")),QHostAddress(tr("1.2.3.20")),dchat);
    QDomElement element = getXmlElement();
    QDomElement ip_listElement = element.firstChildElement();
    while (!ip_listElement.isNull()) {
        if (ip_listElement.tagName() == tr("ip_list") && ip_listElement.attribute(tr("key"))==tr("range_ip")) 
            ip_lists << new dRangeIPEx(ip_listElement,this,dchat);
        if (ip_listElement.tagName() == tr("ip_list") && ip_listElement.attribute(tr("key"))==tr("single_ip"))
            ip_lists << new dSingleIPEx(ip_listElement,this,dchat);
        ip_listElement = ip_listElement.nextSiblingElement();
    }
//    foreach( QHostAddress ip ,dchat->get_ip_list() )
//            qDebug() << ip.toString();

}
dSettingNet::~dSettingNet()
{
   // saveSetting();
};

QWidget *dSettingNet::createWidget()
{
    QWidget * widget =  new QWidget();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(1);
    layout->setSpacing(5);
    QFrame *label = new QFrame();
    label->setFrameStyle(QFrame::Box | QFrame::Raised);
        QVBoxLayout *netLayout = new QVBoxLayout;
            QHBoxLayout *networkModuleLayout = new QHBoxLayout;
                networkModuleLayout->setSpacing(5);
                networkModuleLayout->addWidget(new QLabel(tr("Библиотека работы с Udp:")));
                networkModuleComboBox = new QComboBox;
                networkModuleComboBox->addItem(tr("Модуль Qt 4"));
// Сделаем все как пологается....
#ifdef Q_WS_WIN
                networkModuleComboBox->addItem(tr("Модуль dUdpSocket.dll (только в ОС Windows)"));
                networkModuleComboBox->setCurrentIndex(toInt(tr("network_module"),tr("value"),0));
#else
                networkModuleComboBox->setCurrentIndex(0);
#endif
                networkModuleLayout->addWidget(networkModuleComboBox);
                networkModuleLayout->addStretch ( 5 );       
            netLayout->addItem(networkModuleLayout);
            netLayout->addWidget(new QLabel(tr("<b>Замечено</b>, что в ОС Windows библиотека Qt не корректно работает с Udp протоколом,<br> что может привести к зависанию чата.")));
            QHBoxLayout *portLayout = new QHBoxLayout;
                portLayout->setSpacing(5);
                portLayout->addWidget(new QLabel(tr("Порт:")));
                portSpinBox = new QSpinBox;
                portSpinBox->setSingleStep(1);
                portSpinBox->setMinimum(0);
                portSpinBox->setMaximum(65536);
                portSpinBox->setValue(toInt(tr("port"),tr("value"),8167));
                portLayout->addWidget(portSpinBox);
                portLayout->addStretch ( 5 );       
            netLayout->addItem(portLayout);
            QHBoxLayout *broadcastIPLayout = new QHBoxLayout;
                broadcastIPLayout->setSpacing(5);
                broadcastIPLayout->addWidget(new QLabel(tr("Широковещательный адрес:")));
                broadcastIPLineEdit = new QLineEdit;
                broadcastIPLineEdit->setInputMask("000.000.000.000;_");
                broadcastIPLineEdit->setText(get(tr("broadcast_ip"),tr("value"),tr("1.2.3.255")));
                broadcastIPLayout->addWidget(broadcastIPLineEdit);
    //            inputMaskLineEdit->setText("00000000");
    
    //            messageMaxSpinBox->setValue(toInt(tr("max_message"),tr("value"),30));
                broadcastIPLayout->addStretch ( 5 );       
            netLayout->addItem(broadcastIPLayout);
            QHBoxLayout *buttonLayout = new QHBoxLayout;
                buttonLayout->setSpacing(5);
                QPushButton * useButton = new QPushButton(tr("Применить настройки"));
                connect(useButton, SIGNAL(clicked(bool)), this, SLOT(clickedUseButton(bool)));
                buttonLayout->addWidget(useButton);
                buttonLayout->addStretch ( 5 );       
            netLayout->addItem(buttonLayout);            
        label->setLayout(netLayout);
    layout->addWidget(label);
    QHBoxLayout *timeoutLayout = new QHBoxLayout;
        timeoutLayout->setSpacing(5);
        timeoutLayout->addWidget(new QLabel(tr("TimeOut-время жизни не активного пользователя(сек.):")));
        timeoutSpinBox = new QSpinBox;
        timeoutSpinBox->setSingleStep(1);
        timeoutSpinBox->setMinimum(35);
        timeoutSpinBox->setMaximum(3600);
        timeoutSpinBox->setValue(toInt(tr("timeout"),tr("value"),150));
        connect(timeoutSpinBox, SIGNAL(valueChanged(int)), this, SLOT(timeoutChanged(int)));
        timeoutLayout->addWidget(timeoutSpinBox);
        timeoutLayout->addStretch ( 5 );       
    layout->addItem(timeoutLayout);            
    QHBoxLayout *refreshLayout = new QHBoxLayout;
        refreshLayout->setSpacing(5);
        refreshLayout->addWidget(new QLabel(tr("Интервал обновления списка(отправка массовых эхо-запросов)(сек.):")));
        refreshSpinBox = new QSpinBox;
        refreshSpinBox->setSingleStep(1);
        refreshSpinBox->setMinimum(30);
        refreshSpinBox->setMaximum(3600);
        refreshSpinBox->setValue(toInt(tr("refresh"),tr("value"),60));
        connect(refreshSpinBox, SIGNAL(valueChanged(int)), this, SLOT(refreshChanged(int)));
        refreshLayout->addWidget(refreshSpinBox);
        refreshLayout->addStretch ( 5 );       
    layout->addItem(refreshLayout);    
    QHBoxLayout *refreshInfoLayout = new QHBoxLayout;
        refreshInfoLayout->setSpacing(5);
        refreshInfoLayout->addWidget(new QLabel(tr("Интервал обновления аватара и информации о пользователе(сек.):")));
        refreshInfoSpinBox = new QSpinBox;
        refreshInfoSpinBox->setSingleStep(1);
        refreshInfoSpinBox->setMinimum(30);
        refreshInfoSpinBox->setMaximum(3600);
        refreshInfoSpinBox->setValue(toInt(tr("refresh_info"),tr("value"),80));
        connect(refreshInfoSpinBox, SIGNAL(valueChanged(int)), this, SLOT(refreshInfoChanged(int)));
        refreshInfoLayout->addWidget(refreshInfoSpinBox);
        refreshInfoLayout->addStretch ( 5 );       
    layout->addItem(refreshInfoLayout);   
    layout->addWidget(new QLabel(tr("<br><b>Вид отправления массовых сообщений:</b>")));
        QHBoxLayout *sendTypeLayout = new QHBoxLayout;
        sendTypeLayout->setSpacing(15);
        QComboBox *sendTypeComboBox = new QComboBox;
        sendTypeComboBox->addItem(tr("Широковещательными пакетами"));
        sendTypeComboBox->addItem(tr("Рассылка сообщений по списку адресов"));
        sendTypeComboBox->setCurrentIndex(toInt(tr("send_type"),tr("value"),1));
        connect(sendTypeComboBox, SIGNAL(activated (int)), this, SLOT(sendTypeActivated (int)));
        sendTypeLayout->addWidget (sendTypeComboBox );
        sendTypeLayout->addStretch ( 1 );
    layout->addItem(sendTypeLayout);   
    layout->addWidget(new QLabel(tr("<br><b>Список адресов рассылки:</b>")));
        QHBoxLayout *ipListLayout = new QHBoxLayout;
        ipListLayout->setSpacing(5);
        ipList = new QListWidget();
        
        foreach( dAbstractIPListEx *ip_list ,ip_lists )
        {
            QListWidgetItem *item = new QListWidgetItem(ip_list->get_title(),ipList);
            item->setData(Qt::UserRole,(int)ip_list);
        }
        ipListLayout->addWidget (ipList );
            QVBoxLayout *ipListButtonLayout = new QVBoxLayout;
            ipListButtonLayout->setSpacing(5);
            QPushButton * addRangeButton = new QPushButton(tr("Добавить диапазон"));
            connect(addRangeButton, SIGNAL(clicked()), this, SLOT(clickedAddRangeIPWindowButton()));
            ipListButtonLayout->addWidget( addRangeButton );                   
            QPushButton * addSingleButton = new QPushButton(tr("Добавить адрес"));
            connect(addSingleButton, SIGNAL(clicked()), this, SLOT(clickedAddSingleIPWindowButton()));
            ipListButtonLayout->addWidget( addSingleButton );                   
            QPushButton * deleteIPButton = new QPushButton(tr("Удалить"));
            connect(deleteIPButton, SIGNAL(clicked()), this, SLOT(clickedDeleteIPButton()));
            ipListButtonLayout->addWidget( deleteIPButton );                   
            ipListButtonLayout->addStretch ( 1 );
        ipListLayout->addItem(ipListButtonLayout);   
        ipListLayout->addStretch ( 1 );
    layout->addItem(ipListLayout);   
    widget->setLayout(layout); 
    return widget; 
};

void dSettingNet::clickedUseButton ( bool checked )
{
	QHostAddress broadcast_ip;
	if( !broadcast_ip.setAddress(broadcastIPLineEdit->text()) )
	{
        QMessageBox::warning (0, tr("Замечание."),
                                 tr("Не правильный формат адреса."),QMessageBox::Ok,0,0);        
        return;
    }
    delete dchat;
    try
    {
        set(tr("network_module"),tr("value"),networkModuleComboBox->currentIndex());
        set(tr("port"),tr("value"),portSpinBox->value());
        set(tr("broadcast_ip"),tr("value"),broadcastIPLineEdit->text());
        dchat = new dService(application->get_managerEx(),portSpinBox->value(),networkModuleComboBox->currentIndex());
        dchat->onLog(stdout, 0 );	// Выведем лог в стандартный поток.    
        dchat->set_broadcast_ip(broadcast_ip);
        
        if( toInt(tr("send_type"),tr("value"),1) == 0)
            dchat->set_send_type(dService::broadcast_ip_type);
        else
            dchat->set_send_type(dService::list_ip_type);
            
        foreach( dAbstractIPListEx *ip_list ,ip_lists )
            ip_list->addListToService(dchat);
    
        application->get_managerEx()->send_mass_echo();
    }
    catch( dService::dServiceError error )
    {
        if( error == dService::load_plugin )
            QMessageBox::critical(0, tr("Error."),
                                     tr("Не могу загрузить сетевую библиотеку dUdpSocket.dll"),QMessageBox::Ok,0,0);
        if( error == dService::init )
            QMessageBox::critical(0, tr("Error."),
                                     tr("Не могу инициализировать сокет. Возможно, на этом порту\n висят другие программы. Выключите их и зайдите\n Настройки->Сетивые->Применить."),QMessageBox::Ok,0,0);
        dchat = 0;
    }
    catch(...)
    {
        QMessageBox::critical(0, tr("Error."),
                                 tr("Ошибка при инициализации сети."),QMessageBox::Ok,0,0);
        dchat = 0;
    }
}

void dSettingNet::timeoutChanged( int _value )
{
    set(tr("timeout"),tr("value"),_value);
    application->get_managerEx()->set_timeout(_value);
}
void dSettingNet::refreshChanged( int _value )
{
    set(tr("refresh"),tr("value"),_value);
    application->get_managerEx()->set_interval_refresh(_value);
}
void dSettingNet::refreshInfoChanged( int _value )
{
    set(tr("refresh_info"),tr("value"),_value);
    application->get_managerEx()->set_interval_ping(_value);
}

// При нажатии клавиши добавления диапазона адресов.
void dSettingNet::clickedAddRangeIPWindowButton()
{
    rangeIPWindow =  new QWidget();
    rangeIPWindow->setWindowTitle(tr("Добавить диапазон адресов:"));
    
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(1);
    layout->setSpacing(5);
    layout->addWidget(new QLabel(tr("Начиная с:")));

    IP1LineEdit = new QLineEdit;
    IP1LineEdit->setInputMask("000.000.000.000;_");
    IP1LineEdit->setText(tr("192.168.1.1"));
    layout->addWidget(IP1LineEdit);

    layout->addWidget(new QLabel(tr("по:")));
    IP2LineEdit = new QLineEdit;
    IP2LineEdit->setInputMask("000.000.000.000;_");
    IP2LineEdit->setText(tr("192.168.1.254"));
    layout->addWidget(IP2LineEdit);
    
    QPushButton * addButton = new QPushButton(tr("Добавить"));
    connect(addButton, SIGNAL(clicked()), this, SLOT(clickedAddRangeIPButton()));
    layout->addWidget( addButton );                   

    rangeIPWindow->setLayout(layout); 
    rangeIPWindow->show(); 
}
void dSettingNet::clickedAddRangeIPButton()
{
    QDomElement ip_listElement = getXmlElement().ownerDocument().createElement(tr("ip_list"));
    getXmlElement().appendChild(ip_listElement);
    ip_listElement.setAttribute(tr("key"),tr("range_ip"));
    QDomElement range_ipElement = getXmlElement().ownerDocument().createElement(tr("range_ip"));
    ip_listElement.appendChild(range_ipElement);
    QDomElement rangeElement = getXmlElement().ownerDocument().createElement(tr("range"));
    range_ipElement.appendChild(rangeElement);
    rangeElement.setAttribute(tr("border1"),IP1LineEdit->text());
    rangeElement.setAttribute(tr("border2"),IP2LineEdit->text());
    
    dAbstractIPListEx* ip_list = new dRangeIPEx(ip_listElement,this,dchat);
    ip_lists << ip_list;
    QListWidgetItem *item = new QListWidgetItem(ip_list->get_title(),ipList);
    item->setData(Qt::UserRole,ip_list);
    delete rangeIPWindow;
}
// При нажатии клавиши добавления адреса.
void dSettingNet::clickedAddSingleIPWindowButton()
{
    QWidget * singleIPWindow =  new QWidget();
    singleIPWindow->setWindowTitle(tr("Добавить адрес:"));
    
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(1);
    layout->setSpacing(5);
    IP3LineEdit = new QLineEdit;
    IP3LineEdit->setInputMask("000.000.000.000;_");
    IP3LineEdit->setText(tr("192.168.1.1"));
    layout->addWidget(IP3LineEdit);
    
    QPushButton * addButton = new QPushButton(tr("Добавить"));
    connect(addButton, SIGNAL(clicked()), this, SLOT(clickedAddSingleIPButton()));
    layout->addWidget( addButton );                   

    singleIPWindow->setLayout(layout); 
    singleIPWindow->show(); 
}

// При нажатии клавиши добавления адреса.
void dSettingNet::clickedAddSingleIPButton()
{
    QDomElement ip_listElement = getXmlElement().ownerDocument().createElement(tr("ip_list"));
    getXmlElement().appendChild(ip_listElement);
    ip_listElement.setAttribute(tr("key"),tr("single_ip"));
    QDomElement range_ipElement = getXmlElement().ownerDocument().createElement(tr("single_ip"));
    ip_listElement.appendChild(range_ipElement);
    QDomElement rangeElement = getXmlElement().ownerDocument().createElement(tr("ip"));
    range_ipElement.appendChild(rangeElement);
    rangeElement.setAttribute(tr("value"),IP3LineEdit->text());
    
    dAbstractIPListEx* ip_list = new dSingleIPEx(ip_listElement,this,dchat);
    ip_lists << ip_list;
    QListWidgetItem *item = new QListWidgetItem(ip_list->get_title(),ipList);
    item->setData(Qt::UserRole,ip_list);
    delete singleIPWindow;
}

// При нажатии клавиши удаления адреса.
void dSettingNet::clickedDeleteIPButton()
{
    if( ipList->currentRow() != -1 )
    {
        QListWidgetItem *item = ipList->currentItem();
        dAbstractIPListEx *ip_list = (dAbstractIPListEx*)item->data(Qt::UserRole).toInt();
        
        getXmlElement().removeChild(ip_list->getParentXmlElement());
        delete item;
        ip_lists.removeAll(ip_list);
    }
}

void dSettingNet::sendTypeActivated( int _index )
{
    if( _index == 0)
        dchat->set_send_type(dService::broadcast_ip_type);
    else
        dchat->set_send_type(dService::list_ip_type);

    set(tr("send_type"),tr("value"),_index);
}


