#include "dmanager.h"
#include "dservice.h"
#include "duser.h"

#include <QtNetwork>
//***************************************************************
// КОНСТРУКТОР.
dManager::dManager( QObject  *_parent ):
            QObject(_parent),
// По умолчанию интервал посылания массовых эхо запросов равен: 60 сек.
            interval_refresh(60),
// По умолчанию интервал посылания пинга(эхо-запроса) каждому 
// пользователю равен: 40 сек.
            interval_ping(40),
// По умолчанию время жизни не активного пользователя равно: 150 сек.
            timeout(150)
{   /*ПУСТОЙ*/
    refreshTimerID = startTimer( interval_refresh*1000 );
    
    QHostInfo hostInfo(QHostInfo::fromName(QHostInfo::localHostName()));
    QList<QHostAddress> adr_list= hostInfo.addresses();
    qDebug() << "LocalIP: " << adr_list[0].toString();
    localIP = adr_list[0];
};

//***************************************************************
// МЕТОДЫ ДОБОВЛЯЮТ(УДАЛЯЮТ) СЕРВИС В СПИСОК.
dService *dManager::addService(dService * service)
{
	if ( !service )
		return NULL;

// Проверка на дублирование. Если сервис уже присутсвует в списке,
// тогда зачем его вносить снова? Проверка проводиться на сходство
// адресов объектов.
	QList<dService*>::iterator it_ser = services.begin();
	while (it_ser != services.end()) 
	{
		if ( service == *it_ser)
			return NULL;
		++it_ser;
	}

	services.push_back(service);
	return service;
};

void dManager::deleteService(dService * service)
{
	services.removeAll(service);
};

//***************************************************************
//  МЕТОДЫ ДОБОВЛЯЮТ(УДАЛЯЮТ) ПОЛЬЗОВАТЕЛЯ В СПИСОК.
dUser *dManager::addUser(dUser * user)
{
	if ( !user )
		return NULL;

// Проверка на дублирование. Если в списке уже находится подобный объект,
// то происходит выход из процедуры. Равенство объектов определяется перег-
// руженным оператором ==.
	QList<dUser*>::iterator it_usr = users.begin();
	while (it_usr != users.end())
	{
		if ( *user == **it_usr)
			return NULL;
		++it_usr;
	}
	
	users.push_back(user);
	//qDebug() << "ADD USER " <<user->get_name() << ":" << this->get_user_count() << endl;

	return user;
}
void dManager::deleteUser(dUser * user)
{
	users.removeAll(user);
}

//***************************************************************
//  ДЕСТРУКТОР :)
dManager::~dManager()
{
    QList<dUser*> _users = users;
	QList<dUser*>::iterator it_usr =_users.begin();
	while (it_usr != _users.end()) 
	{
		delete *it_usr;
		++it_usr;
	}

    QList<dService*> _services = services;
	QList<dService*>::iterator it_ser = _services.begin();
	while (it_ser != _services.end()) 
	{
		delete *it_ser;
		++it_ser;
	}

}; 

//***************************************************************
// ВОЗВРАЩАЕТ КОЛИЧЕСТВО ПОЛЬЗОВАТЕЙ В СПИСКЕ.
uint dManager::get_user_count() const
{
	return users.count();
}

//***************************************************************
//  МЕТОДЫ ВЫПОЛНЯЮТ ПОИСК ПОЛЬЗОВАТЕЛЯ В СПИСКЕ.
dPUser dManager::find_user( const QHostAddress &_ip, const QString &_name)
{
    foreach( dUser* usr, users )
	{
		if( _name == usr->get_name() &&_ip == usr->get_ip() )
			return usr->get_pointer();
	}
	return dPUser();
}
dPUser dManager::find_user(const char *_ip, const char *_name)
{
    QString ip_qstring = QString::fromLocal8Bit(_ip);
    QString name_qstring = QString::fromLocal8Bit(_name);
	return find_user(ip_qstring, name_qstring );
}
dPUser dManager::find_user(const QString &_ip, const QString &_name)
{
	QHostAddress address;
	address.setAddress(_ip);
	return find_user(address, _name );
}

//***************************************************************
//  МЕТОДЫ ВЫПОЛНЯЮТ ПОИСК ПОЛЬЗОВАТЕЛЯ В СПИСКЕ C УКАЗАНИЕМ 
// ТОЛЬКО IP АДРЕСА.
QList<dPUser> dManager::find_users_by_ip( const QHostAddress &_ip )
{
    QList<dPUser> user_list;
	dUser* usr;
	QList<dUser*>::iterator it_usr = users.begin();
	while (it_usr != users.end()) 
	{
		usr = *it_usr;
		if( _ip == usr->get_ip() )
			user_list.push_back(usr->get_pointer());
		++it_usr;
	}
	return user_list;
};

QList<dPUser> dManager::get_users() const
{ 
    QList<dPUser> user_list;
	foreach( dUser *usr, users ) 
        user_list.push_back(usr->get_pointer());
	return user_list;
};

//***************************************************************
//  МЕТОДЫ ОТПРАВКИ МАССОВЫХ СООБЩЕНИЙ.
bool dManager::send_mass( dService::dMessageSendType _msg_send_type,
                          dMessageMassType _msg_mass_type, 
                          dPUser _from, 
                          const QString* _msg)  
{
    if( !_from )
        _from = get_main_user();
        
	// ДАЛЕЕ ИДЕТ ОТПРАВКА СООБЩЕНИЙ НА ВСЕ СЕРВИСЫ.
	// Которые потом потом отправлятся широковешятельными пакетами.
    if( _msg_mass_type == msg_echo      || _msg_mass_type == msg_exit || 
        _msg_mass_type == msg_enter     || _msg_mass_type == msg_rename ||
        _msg_mass_type == msg_channel   || _msg_mass_type == change_topic ||
        _msg_mass_type == msg_channel_me )
    {
        QList<dService*>::const_iterator it_ser = get_services().begin();
        while (it_ser != get_services().end()) 
        {
        
            dService *serv = *it_ser;
            switch( _msg_mass_type )
            {
                case msg_echo:
                    if( !get_main_user() ) return(false);
                    serv->send_mass_echo(_msg_send_type,get_main_user());
                break;
                case msg_enter:
                    if(!_from ) return false;
                    serv->send_mass_enter(_msg_send_type,_from);
                break;
                case msg_exit:
                    if(!_from) return false;
                    serv->send_mass_exit(_msg_send_type,_from);
                break;
                case msg_channel:
                    if( !_from || !_msg ) return false;
                    serv->send_mass_msg_channel(_msg_send_type,_from,*_msg);
                break;
                case msg_channel_me:
                    if( !_from || !_msg ) return false;
                    serv->send_mass_msg_channel_me(_msg_send_type,_from,*_msg);
                break;
                case msg_rename:
                    if( !_from || !_msg ) return false;
                    serv->send_mass_rename(_msg_send_type,_from,*_msg);
                break;
                case change_topic:
                    if( !_msg ) return false;
                    serv->send_mass_change_topic(_msg_send_type,*_msg);
                break;
            }
            ++it_ser;
        }
    }
    return true;
};

bool dManager::send_mass_echo( dService::dMessageSendType _msg_send_type)
{
    send_mass(_msg_send_type,msg_echo);
};
void dManager::send_mass_enter( dPUser _from, dService::dMessageSendType _msg_send_type )
{
    send_mass(_msg_send_type,msg_enter,_from);
};
void dManager::send_mass_exit( dPUser _from, dService::dMessageSendType _msg_send_type )
{
    send_mass(_msg_send_type,msg_exit,_from);
};
/*======================================================================
        УСТАРЕЛО.... В ДАННЫЙ МОМЕТ НЕ ИСПОЛЬЗУЕТСЯ...
void dManager::send_mass_rename(const QString &_oldname, dUser *_from, dService::dMessageSendType _msg_send_type)
{
    send_mass(_msg_send_type,msg_rename,_from,&_oldname);
};

void dManager::send_mass_msg_channel( const QString &_msg, dUser *_from, dService::dMessageSendType _msg_send_type)
{
    send_mass(_msg_send_type,msg_channel,_from,&_msg);	
};
void dManager::send_mass_msg_channel_me(const QString &_msg, dUser *_from, dService::dMessageSendType _msg_send_type)
{
    send_mass(_msg_send_type,msg_channel_me,_from,&_msg);	
};

void dManager::send_mass_change_topic( const QString &_topic, dService::dMessageSendType _msg_send_type )
{
	send_mass(_msg_send_type,change_topic,0,&_topic);	
};
*/

//***************************************************************
// Таймер.... срабатывает каждые 30(уже нет... смотря какие настройки) сек. Для проверки 
void dManager::timerEvent( QTimerEvent *event )
{
    send_mass_echo();
}

// Изменение интервала обновления списка.
// Тут нужно перестроить таймер.
void dManager::set_interval_refresh( uint _interval_refresh )
{ 
    interval_refresh = _interval_refresh; 
    killTimer(refreshTimerID);
    refreshTimerID = startTimer( interval_refresh*1000 );    
};

///////////////////////////////////////////////////////////////////////
// Следующие методы созданы для удобства, их описание можно найти 
// в dUser. И созданы для отправки сообщений сразу нескольким
// пользователям.
bool dManager::send_info_request( const QList<dPUser> &_to, dPUser _from )
{
    if( !get_users().contains(_from) )
        return false;
    foreach( dPUser usr, _to)
        if( get_users().contains(usr) )
            usr->send_info_request(_from);
    return true;
};
bool dManager::send_image_request( const QList<dPUser> &_to, dPUser _from )
{
    if( !get_users().contains(_from) )
        return false;
    foreach( dPUser usr, _to)
        if( get_users().contains(usr) )
            usr->send_image_request(_from);
    return true;
};
bool dManager::send_msg( const QList<dPUser> &_to,const QString & _msg, dPUser _from, bool _html )
{
    if( !get_users().contains(_from) )
        return false;
    foreach( dPUser usr, _to)
        if( get_users().contains(usr) )
            usr->send_msg(_msg,_from,_html);
    return true;
};

bool dManager::send_msg_mass( const QList<dPUser> &_to,const QString & _msg, dPUser _from, bool _html )
{
    if( !get_users().contains(_from) )
        return false;
    foreach( dPUser usr, _to)
        if( get_users().contains(usr) )
            usr->send_msg_mass(_msg,_from,_html);
    return true;
};
bool dManager::send_msg_channel( const QList<dPUser> &_to,const QString & _msg, dPUser _from )
{
    if( !get_users().contains(_from) )
        return false;
    foreach( dPUser usr, _to)
        if( get_users().contains(usr) )
            usr->send_msg_channel(_msg,_from);
    return true;
};
bool dManager::send_rename( const QList<dPUser> &_to,const QString & _oldname, dPUser _from )
{
    if( !get_users().contains(_from) )
        return false;
    foreach( dPUser usr, _to)
        if( get_users().contains(usr) )
            usr->send_rename(_oldname,_from);
    return true;
};
bool dManager::send_msg_channel_me( const QList<dPUser> &_to,const QString & _msg, dPUser _from )
{
    if( !get_users().contains(_from) )
        return false;
    foreach( dPUser usr, _to)
        if( get_users().contains(usr) )
            usr->send_msg_channel_me(_msg,_from);
    return true;
};
bool dManager::send_msg_beep( const QList<dPUser> &_to, dPUser _from )
{
    if( !get_users().contains(_from) )
        return false;
    foreach( dPUser usr, _to)
        if( get_users().contains(usr) )
        {
            usr->send_msg_beep(_from);
        }
    return true;
};
bool dManager::send_auto_answer( const QList<dPUser> &_to, dPUser _from )
{
    if( !get_users().contains(_from) )
        return false;
    foreach( dPUser usr, _to)
        if( get_users().contains(usr) )
            usr->send_auto_answer(_from);
    return true;
};

bool dManager::send_change_topic( const QList<dPUser> &_to, const QString & _topic )
{
    foreach( dPUser usr, _to)
        if( get_users().contains(usr) )
            usr->send_change_topic(_topic);
    return true;
};

