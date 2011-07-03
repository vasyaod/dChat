#ifndef DLOCALAUTOUSEREX_H
#define DLOCALAUTOUSEREX_H

#include <QtGui>

#include "dlocaluserex.h"
#include "dabstractusercreator.h"

#define AUTO_USER_KEY "AUTO_USER"

class dLocalAutoUserEx: public dLocalUserEx
{
	public:
		dLocalAutoUserEx(dManagerEx * _manager, const QString &_name,  QDomElement &_parentXmlElement, dSetting *_parentSetting = 0);
		~dLocalAutoUserEx();

	//	virtual QString get_type() const{ return tr(AUTO_USER_KEY); };

    ///////////////////// ѕерегружаем событи€. /////////////////////
    // —обытие происходит, когда приходит звуковой сигнал.
		virtual void event_msg_beep( dPUser _from );
    // —обытие происходит, когда приходит личное сообщение.
		virtual void event_msg_personal( dPUser _from, const QString & _msg, bool html = false);
    // —обытие происходит, при получении массового сообщени€.
};

class dLocalAutoUserCreator : public dAbstractUserCreator
{
    public:
        dLocalAutoUserCreator(){};
        virtual dPUser create( dManagerEx * _manager, const QString &_name, QDomElement &_parentXmlElement, dSetting *_parentSetting = 0)
        {  
            dUser *usr = new dLocalAutoUserEx( _manager, _name, _parentXmlElement, _parentSetting );
            return usr->get_pointer();
        };
        QString getKey() const { return QString(AUTO_USER_KEY); };
        QString getTitle() const { return QString("ѕростой авто-ответчик."); };
        QString getDescription() const { return QString("ѕосылает обратно авто-ответ в виде обычного сообщени€."); };
};


#endif	//DLOCALAUTOUSEREX_H
