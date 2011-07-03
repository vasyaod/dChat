#include "dlocaluser.h"
#include "dmanager.h"
/***************** КОНСТРУКТОРЫ И ДЕСТРУКТОРЫ *******************/
dLocalUser::dLocalUser(	dManager * _manager, 
						const QString &_name ):
		dUserEx(_manager,_manager->get_localAddress(),_name)
{ 
    set_xml_protocol(1);        // Версия XML протакола равна 1.
    
	set_login(QString::fromLocal8Bit("CHUGUN"));
	set_version (QString::fromLocal8Bit("anti-mat"));
	set_host(QString::fromLocal8Bit("CHUGUN"));
	set_memory(QString::fromLocal8Bit("Теробайт!"));
	set_auto_answer(QString::fromLocal8Bit("Ни что не помогает так расслабиться, как хороший ананизм!!!"));
	set_percent(QString::fromLocal8Bit("Не ваше дело!"));
	set_sex(0);          // Мужской
    set_activity(true);  // Активен.
    set_mode(0);         // Нормальный.
    
	// Если "основной" юзер не установлен, то его следует установить!
	// Причем этот юзер будет текущим.
	if( !get_manager()->get_main_user() )
	{
        set_main_user();
        get_manager()->send_mass_echo();
    }

	//get_manager()->send_mass_enter(this);
};

dLocalUser::~dLocalUser()
{
    
    if( get_manager()->get_main_user() == get_pointer() )
        foreach (dPUser usr, get_manager()->get_users())
        {
             if ( !(get_pointer() == usr) )
                  if( usr->set_main_user() )
                      break;
        }
    
    // Если основного пользователя всё же не удалось сменить,
    // тогда занулим его.
    if( get_manager()->get_main_user() == get_pointer() )
        get_manager()->set_main_user(dPUser());
//	get_manager()->send_mass_exit(this);
}
/************ МЕТОД УСТАНАВЛИВАЕТ ОСНОВНОГО ПОЛЬЗОВАТЕЛЯ ***********/
bool dLocalUser::set_main_user()
{
    get_manager()->set_main_user(get_pointer());
	return true;
}

void dLocalUser::event_echo_request( dPUser _from )
{
	_from->send_echo_answer(get_pointer());
};

void dLocalUser::event_info_request( dPUser _from )
{
	_from->send_info_answer(get_pointer());
};

void dLocalUser::event_msg_enter( dPUser _from )
{
	_from->send_current_topic(get_manager()->get_main_user()->get_topic());
    dUser::event_msg_enter(_from);
};

void dLocalUser::event_image_request( dPUser _from, const QString &_id )
{
    _from->send_image_answer(_id,get_pointer());
    dUser::send_image_answer(_id, _from);
};
void dLocalUser::event_msg_personal( dPUser _from, const QString & _msg, bool _html )
{
    _from->send_auto_answer(get_pointer());
    dUser::event_msg_personal(_from,_msg,_html);
}
void dLocalUser::event_msg_mass( dPUser _from, const QString & _msg, bool _html )
{
    _from->send_auto_answer(get_pointer());    
    dUser::event_msg_mass(_from,_msg,_html);
}

/// Переопределим функции отправки некоторых сообщений.....
void dLocalUser::send_msg_mass( const QString & _msg, dPUser _from, bool _html )
{
    get_manager()->event_msg_mass(_from,get_pointer(),_msg,_html);
    event_msg_mass( _from , _msg, _html);    
};
void dLocalUser::send_msg( const QString & _msg, dPUser _from, bool _html )
{
    
    get_manager()->event_msg_personal(_from,get_pointer(),_msg,_html);
    event_msg_personal( _from , _msg, _html);
};
void dLocalUser::send_msg_beep( dPUser _from )
{
    get_manager()->event_msg_beep(_from,get_pointer());
    event_msg_beep( _from );    
};
void dLocalUser::send_auto_answer( dPUser _from )
{
    get_manager()->event_msg_auto_answer(_from,get_pointer(),_from->get_auto_answer());
    event_msg_auto_answer(_from,_from->get_auto_answer());
};
void dLocalUser::event_xml( dPUser _from, const QDomElement &messageElement )
{

};
