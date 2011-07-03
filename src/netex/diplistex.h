#ifndef DIPLISTEX_H
#define DIPLISTEX_H

#include "../net/dservice.h"
#include "../dsetting.h"

class dSetting;

class dAbstractIPListEx :public dSetting, public dAbstractIPList
{
    public:
        dAbstractIPListEx( const QString &_key, QDomElement &_parentElement, dSetting *_parent, dService *_service = 0):
                    dSetting(_key,_parentElement,_parent),
                    dAbstractIPList(_service){};
        virtual const QList<QHostAddress> &get_ip_list() const= 0;
        virtual const QString &get_title() const= 0;
};

// Класс представляет собой диапозон IP адресов.
class dRangeIPEx : public dAbstractIPListEx
{
    private:
        QList<QHostAddress> ip_list;
        QString title;
    public:
        dRangeIPEx( QDomElement &_parentElement, dSetting *_parent, dService *_service = 0 );
//        ~dRangeIPEx();
        virtual const QList<QHostAddress> &get_ip_list() const{ return ip_list; };
        virtual const QString &get_title() const{ return title; };
};

// Класс представляет один IP адрес.
class dSingleIPEx : public dAbstractIPListEx
{
    private:
        QList<QHostAddress> ip_list;    
        QString title;
    public:
        dSingleIPEx( QDomElement &_parentElement, dSetting *_parent, dService *_service = 0 );
        virtual const QList<QHostAddress> &get_ip_list() const{ return ip_list; };
        virtual const QString &get_title() const { return title; };
};
#endif	//DIPLISTEX_H

