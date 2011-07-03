#ifndef DABSTRACTREMOTEUSERCREATOR_H
#define DABSTRACTREMOTEUSERCREATOR_H

#include <QHostAddress>
#include <QString>

class dService;
class dPUser;
//#include "duser.h"

class dAbstractRemoteUserCreator
{
    public:
        dAbstractRemoteUserCreator(){};
        virtual dPUser create( dService * _service, const QHostAddress &_ip, const QString &_name ) const = 0;
};
#endif // DABSTRACTREMOTEUSERCREATOR_H

