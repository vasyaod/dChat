#ifndef DABSTRACTUSERCREATOR_H
#define DABSTRACTUSERCREATOR_H

#include <QString>
#include <QDomElement>

class dPUser; 
class dManagerEx; 
class dSetting;

// Обеспечивает интерфейс для подключения локальных пользователей.
class dAbstractUserCreator
{
    public:
        dAbstractUserCreator(){};
        virtual dPUser create( dManagerEx *_manager, const QString &_name, QDomElement &_parentXmlElement, dSetting *_parentSetting ) = 0;
        virtual QString getKey() const = 0;
        virtual QString getTitle() const = 0;
        virtual QString getDescription() const{ return QString(); };
};

#endif	//DABSTRACTUSERCREATOR_H

