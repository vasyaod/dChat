#include "diplistex.h"

dRangeIPEx::dRangeIPEx( QDomElement &_parentElement,
                        dSetting *_parent,
                        dService *_service):
            dAbstractIPListEx(tr("range_ip"),_parentElement,_parent,_service)
{
    setNode(false);
    QHostAddress border1; 
    QHostAddress border2;
    if( border1.setAddress(get(tr("range"),tr("border1"),tr("1.2.2.1"))) &&
        border2.setAddress(get(tr("range"),tr("border2"),tr("1.2.3.254"))))
    {
        quint32 ip1 = border1.toIPv4Address();
        quint32 ip2 = border2.toIPv4Address();
        if( ip1 > ip2 )
        {
            quint32 ip3 = ip1;
            ip1 = ip2;
            ip2 = ip3;
        }
        
        for( quint32 i = ip1; i <= ip2; i++ )
            if( !QHostAddress(i).toString().contains(tr("255")) && 
                !QHostAddress(i).toString().contains(tr(".0")) )
            {
         //       qDebug() << QHostAddress(i).toString();
                ip_list << QHostAddress(i);
            }
        title = tr("Диапазон: %1 - %2").arg(border1.toString()).arg(border2.toString());
    }
    else
        title = tr("Не верный формат адресов.");
    
    
}

dSingleIPEx::dSingleIPEx( QDomElement &_parentElement,
                        dSetting *_parent,
                        dService *_service):
            dAbstractIPListEx(tr("single_ip"),_parentElement,_parent,_service)
{
    setNode(false);
    QHostAddress ip; 
    if( ip.setAddress(get(tr("ip"),tr("value"),tr("1.2.3.1"))))
    {
    //    qDebug() << ip.toString();
        ip_list << ip;
        title = tr("IP: %1").arg(ip.toString());
    }

}

/*
dRangeIPEx::~dRangeIPEx()
{

}

*/


