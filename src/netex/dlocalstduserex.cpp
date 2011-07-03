#include "dlocalstduserex.h"
#include "dmanagerex.h"

#include "../dchatapplication.h"
#include "../dwarningwindow/dwarningwindow.h"

//***************** ÊÎÍÑÒÐÓÊÒÎÐÛ È ÄÅÑÒÐÓÊÒÎÐÛ *******************
dLocalStdUserEx::dLocalStdUserEx(	dManagerEx * _manager, 
                            const QString &_name,
                            QDomElement &_parentXmlElement, 
                            dSetting *_parentSetting ):
            dLocalUserEx(_manager,_name,tr(STD_USER_KEY),_parentXmlElement,_parentSetting)
{ 
};
    
dLocalStdUserEx::~dLocalStdUserEx()
{
}

void dLocalStdUserEx::event_msg_beep( dPUser _from )
{
    application->warning_window->slot_msg_beep(_from,get_pointer());
    dLocalUser::event_msg_beep(_from);
}

void dLocalStdUserEx::event_msg_personal( dPUser _from, const QString & _msg, bool _html )
{

    application->warning_window->slot_msg_personal(_from,get_pointer(),_msg);
    application->createMessageEditor( _from,get_pointer(),_msg,tr("Îò: %1 (IP:%2)").arg(_from->get_name()).arg(_from->get_ip().toString()),dChatApplication::msg_personal,false,_html);

  //  messageEditor->setWindowState(Qt::WindowMinimized);
   // messageEditor->lower();
   // QWidget * activeWindow = QApplication::activeWindow();
    //messageEditor->setDisabled ( true );
   // messageEditor->setVisible( true );
 //   messageEditor->showMinimized();
  //  activeWindow->activateWindow();
  //  activeWindow->setFocus(Qt::OtherFocusReason);
  
    dLocalUserEx::event_msg_personal(_from,_msg,_html);
    
}
void dLocalStdUserEx::event_msg_mass( dPUser _from, const QString & _msg, bool _html )
{
    application->warning_window->slot_msg_mass(_from,get_pointer(),_msg);
    dLocalUserEx::event_msg_mass(_from,_msg,_html);
}


