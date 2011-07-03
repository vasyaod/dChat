#include "dplcommand.h"

#include "../dchatgemstone.h"
#include "dsettingplcommand.h"
#include "../net/dmanager.h"

bool dPlCommand::init( dChatGemstone *chatGemstone )
{
    dChatInterface *chatInterface = *chatGemstone;
    if( !chatInterface )
        return false;   // Интерфейс не открыт...

    dContextUserMenuInterface *contextUserMenuInterface = *chatGemstone;
    if( !contextUserMenuInterface )
        return false;   // Интерфейс не открыт...

    manager = chatInterface->manager();

    setting = new dSettingPLCommand(tr("pl_command"),chatInterface->settingPlugins(),this);
    setting->setTitle(tr("НАСТРОЙКИ ПЛАГИНА: Выполнение команды."));
    setting->setNode(false);

    
    commandAct = new QAction(setting->get(tr("item_name"),tr("value"),tr("Выполнить команду")), this);
    commandAct->setIcon(QIcon(tr("plugins/dplcommand/run16x16.png")));
    contextUserMenuInterface->addAction(commandAct);
    connect(commandAct, SIGNAL(triggered()), this, SLOT(doCommand()));

    command = setting->get(tr("command"),tr("value"),tr("explorer  ftp://$ip"));
    
    delete contextUserMenuInterface;
    delete chatInterface;
    return true;
};

void dPlCommand::doCommand()
{

    foreach(dPUser user, manager->getSelectedUserToModel() )
    {
        QString command_temp = command;
        command_temp.replace(tr("$ip"),user->get_ip().toString());
        command_temp.replace(tr("$name"),user->get_name());
        command_temp.replace(tr("$host"),user->get_host());
        QProcess::execute(command_temp);
    }
}

void dPlCommand::itemNameEdited( const QString& _itemName)
{
    commandAct->setText(_itemName);
    setting->set(tr("item_name"),tr("value"),_itemName);
};

void dPlCommand::commandEdited( const QString& _itemName)
{
    command = _itemName;
    setting->set(tr("command"),tr("value"),_itemName);
};

QWidget *dSettingPLCommand::createWidget()
{
    QWidget * widget =  new QWidget();
    
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(1);
    layout->setSpacing(5);
    
    layout->addWidget ( new QLabel(tr("Название пункта в контекстном меню:")) );
    QLineEdit *itemNameLineEdit = new QLineEdit(plCommand->commandAct->text());
    connect(itemNameLineEdit, SIGNAL(textEdited(const QString&)), plCommand, SLOT(itemNameEdited(const QString&)));
    layout->addWidget ( itemNameLineEdit );

    layout->addWidget ( new QLabel(tr("Выполняемая команда, есть возможность использовать следующие переменные:\n   $ip - адрес пользователя;\n   $name - имя пользователя;\n   $host - имя машины пользователя ")) );
    QLineEdit *commandLineEdit = new QLineEdit(plCommand->command);
    connect(commandLineEdit, SIGNAL(textEdited(const QString&)), plCommand, SLOT(commandEdited(const QString&)));
    layout->addWidget ( commandLineEdit );
    
    widget->setLayout(layout); 
    return widget; 
};





