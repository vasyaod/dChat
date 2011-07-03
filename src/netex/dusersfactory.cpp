#include "dusersfactory.h"
#include "dlocaluserex.h"
#include "dabstractusercreator.h"

QList<QString> dUsersFactory::keys() const
{
    return userCreatorHash.keys();
};

QString dUsersFactory::title( const QString & _key ) const
{
    return titleHash.value(_key);
};

QString dUsersFactory::description( const QString & _key ) const
{
    return descriptionHash.value(_key);
};

dPUser dUsersFactory::create( const QString & _key, dManagerEx *_manager, const QString &_name, QDomElement &_parentXmlElement, dSetting *_parentSetting )
{
    if( userCreatorHash.contains(_key) )
    {
        dAbstractUserCreator *userCreator= userCreatorHash.value(_key);
        return userCreator->create( _manager, _name, _parentXmlElement, _parentSetting);
    }
    return dPUser();
}
void dUsersFactory::addUserCreator( dAbstractUserCreator *_userCreator)
{
    userCreatorHash.insert(_userCreator->getKey(),_userCreator);
    titleHash.insert(_userCreator->getKey(),_userCreator->getTitle());
    descriptionHash.insert(_userCreator->getKey(),_userCreator->getDescription());
};

void dUsersFactory::deleteUserCreator( dAbstractUserCreator *_userCreator )
{
    QString key = userCreatorHash.key(_userCreator);
    userCreatorHash.remove(key);   
    titleHash.remove(key);   
    descriptionHash.remove(key);   
}

bool dUsersFactory::contains( const QString &_key) const
{
    return descriptionHash.contains(_key);
}
