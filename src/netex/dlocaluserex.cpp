#include "dlocaluserex.h"
#include "dmanagerex.h"
#include "dsettinglocaluser.h"

#include "../dchatapplication.h"
//#include "../dtopicwindow/dtopicwindow.h"
//#include "../dchannelwindow/dchannelwindow.h"
#include "../dwarningwindow/dwarningwindow.h"
#include "../duserwindow.h"

#include <QHostInfo>

//***************** КОНСТРУКТОРЫ И ДЕСТРУКТОРЫ *******************
dLocalUserEx::dLocalUserEx(	dManagerEx * _manager, 
                            const QString &_name,
                            const QString &_user_type,
                            QDomElement &_parentXmlElement, 
                            dSetting *_parentSetting ):
            user_type(_user_type),
            dLocalUser(_manager,_name)
{ 
    
    application = qobject_cast<dChatApplication*>(QApplication::instance());
    
	set_version (tr("%1-%2").arg(application->applicationName()).arg(get_type()));
	set_host(QHostInfo::localHostName());
	set_sex(0);          // Мужской
    set_activity(true);  // Активен.
    set_mode(0);         // Нормальный.

    userMenuAct = new QAction(get_name(), this);
    userMenuAct->setCheckable(true);
	if( get_manager()->get_main_user() == get_pointer())
        userMenuAct->setChecked(true);
    connect(userMenuAct, SIGNAL(triggered(bool)), this, SLOT(setMainUserTriggered(bool)));

	application->user_window->getUsersMenu()->addAction(userMenuAct);
	application->user_window->getUsersActionGroup()->addAction(userMenuAct);

    setting = new dSettingLocalUser(_parentXmlElement,_parentSetting,this);
#ifndef D_DEBUG
    // Исли режим не рассивный то пошлем пользователям сообщение о входе в чат.
    if( !setting->hasPassiveMode() )
        get_manager()->send_mass_enter(get_pointer());
#endif

};
    
dLocalUserEx::~dLocalUserEx()
{
#ifndef D_DEBUG
    // Исли режим не рассивный то пошлем пользователям сообщение о выходе из чата.
    if( !setting->hasPassiveMode() )
        get_manager()->send_mass_exit(get_pointer(),dService::broadcast_ip_type);
#endif
	delete userMenuAct;
    delete setting;
}

bool dLocalUserEx::set_main_user()
{
    userMenuAct->setChecked(true);
	return dLocalUser::set_main_user();
}
bool dLocalUserEx::set_name(const QString &_name)
{
    QString _oldname = get_name();
    bool out = dLocalUser::set_name(_name);
    if ( out ) 
    {
        userMenuAct->setText(_name);
        get_manager()->send_rename(get_manager()->get_users(),_oldname,get_pointer());
    }
	return out;
}
void dLocalUserEx::set_avatar(const QPixmap &_avatar)
{
    userMenuAct->setIcon(QIcon(_avatar));    
	return dLocalUser::set_avatar(_avatar);
}

//====================================================================
// Перегружены из-за возможноси создания пассивного режима
void dLocalUserEx::event_echo_request( dPUser _from )
{
    if( !setting->hasPassiveMode() )
        dLocalUser::event_echo_request(_from);
};
void dLocalUserEx::event_info_request( dPUser _from )
{
    if( !setting->hasPassiveMode() )
        dLocalUser::event_info_request(_from);
};
//====================================================================
/*
void dLocalUserEx::event_current_topic( const QString &_topic )
{
    if( application->get_managerEx()->get_main_user() == this )
    {
        application->topic_window->setTopic(_topic);
    }
};
void dLocalUserEx::event_msg_channel( dUser *_from, const QString & _msg)
{
    if( application->get_managerEx()->get_main_user() == this )
    {
        application->channel_window->addMessage(_from, _msg);
    }   
}

void dLocalUserEx::event_msg_channel_me( dUser *_from, const QString & _msg)
{
    if( application->get_managerEx()->get_main_user() == this )
    {
        application->channel_window->addMessage(_from, _msg);
    }
}
*/
void dLocalUserEx::setMainUserTriggered( bool _checked )
{
    if( _checked )
        dLocalUser::set_main_user();
}


