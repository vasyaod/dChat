#ifndef DUSERSFACTORY_H
#define DUSERSFACTORY_H

#include <QtGui>

//#include "../net/dmanager.h"
#include "dabstractusercreator.h"

class dSetting;
class dSetting;
// Класс описывает фабрику пользователей, которая содержит различные типы
// локальных ползователей, скомпилированных вместе с программой,
// или добаленных плагинами.
class dUsersFactory
{
        QHash<QString, dAbstractUserCreator*> userCreatorHash;
        QHash<QString, QString> titleHash;
        QHash<QString, QString> descriptionHash;
        
    public:
        dUsersFactory(){};
        QList<QString> keys() const;
        bool contains( const QString &_key) const;
        QString title( const QString &_key) const;
        QString description( const QString &_key ) const;
        dPUser create( const QString &_key, dManagerEx *_manager, const QString &_name, QDomElement &_parentXmlElement, dSetting *_parentSetting = 0);
        void addUserCreator( dAbstractUserCreator *_userCreator);
        void deleteUserCreator( dAbstractUserCreator *_userCreator);
};
#endif	//DUSERSFACTORY_H

