#ifndef DLOCALSTDUSEREX_H
#define DLOCALSTDUSEREX_H

#include <QtGui>

#include "dlocaluserex.h"
#include "dabstractusercreator.h"

#define STD_USER_KEY "STD_USER"

class dLocalStdUserEx: public dLocalUserEx
{
	public:
		dLocalStdUserEx(dManagerEx * _manager, const QString &_name,  QDomElement &_parentXmlElement, dSetting *_parentSetting = 0);
		~dLocalStdUserEx();
    
	//	virtual QString get_type() const{ return tr(STD_USER_KEY); };
		
    ///////////////////// ѕерегружаем событи€. /////////////////////
    // —обытие происходит, когда приходит звуковой сигнал.
		virtual void event_msg_beep( dPUser _from );
    // —обытие происходит, когда приходит личное сообщение.
		virtual void event_msg_personal( dPUser _from, const QString & _msg, bool html = false);
    // —обытие происходит, при получении массового сообщени€.
		virtual void event_msg_mass( dPUser _from, const QString & _msg, bool html = false);
};

class dLocalStdUserCreator : public dAbstractUserCreator
{
    public:
        dLocalStdUserCreator(){};
        virtual dPUser create( dManagerEx * _manager, const QString &_name, QDomElement &_parentXmlElement, dSetting *_parentSetting = 0)
        {  
            dUser *usr = new dLocalStdUserEx( _manager, _name, _parentXmlElement, _parentSetting ); 
            return usr->get_pointer();            
        };
        QString getKey() const { return QString(STD_USER_KEY); };
        QString getTitle() const { return QString("—тандартный пользователь."); };
        QString getDescription() const { return QString("—тандартный пользователь."); };
};

#endif	//DLOCALSTDUSEREX_H
