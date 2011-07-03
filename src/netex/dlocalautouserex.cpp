#include "dlocalautouserex.h"
#include "dmanagerex.h"
#include "dsettinglocaluser.h"

#include "../dchatapplication.h"
//#include "../dwarningwindow/dwarningwindow.h"
#include "../duserwindow.h"

#include <QHostInfo>

//***************** ÊÎÍÑÒÐÓÊÒÎÐÛ È ÄÅÑÒÐÓÊÒÎÐÛ *******************
dLocalAutoUserEx::dLocalAutoUserEx(	dManagerEx * _manager, 
                            const QString &_name,
                            QDomElement &_parentXmlElement, 
                            dSetting *_parentSetting ):
            dLocalUserEx(_manager,_name,tr(AUTO_USER_KEY),_parentXmlElement,_parentSetting)
{ 
  /* Îñòàëîñü ïóñòûì */
};
    
dLocalAutoUserEx::~dLocalAutoUserEx()
{   /* Îñòàëîñü ïóñòûì */  }

void dLocalAutoUserEx::event_msg_beep( dPUser _from )
{
   // application->warning_window->slot_msg_beep(_from,this);
    dLocalUser::event_msg_beep(_from);
}

void dLocalAutoUserEx::event_msg_personal( dPUser _from, const QString & _msg, bool _html )
{
    _from->send_msg(get_auto_answer(),get_pointer());
    _from->send_auto_answer(get_pointer());
}
