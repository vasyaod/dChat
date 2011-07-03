#ifndef DPLCOMMAND_H
#define DPLCOMMAND_H

#include <QtGui>
#include "../dplugininterface.h"
class dSetting;
class dManager;

class dPlCommand : public QObject, public dChatPluginInterface
{
    Q_OBJECT
    Q_INTERFACES(dChatPluginInterface)
    private:
        dSetting *setting; // Настройки плагина....
        dManager *manager; // Менеджер чата...
    public:
        QAction *commandAct;
        QString command;

        dPlCommand( QObject * _parent = 0 ):QObject(_parent){};
        ~dPlCommand(){};
        
        virtual bool init( dChatGemstone *chatGemstone );
        virtual QString key(){ return tr("dPlCommand"); };
        virtual QString title(){ return  tr("Выполняет команду системы, при этом ей могут передоваться различные параметры(IP пользователя, имя пользователя, host пользователя)."); };

    public slots:
        void doCommand();
        void itemNameEdited( const QString& _itemName);
        void commandEdited( const QString& _inemName);

};

#endif // DPLCOMMAND_H



