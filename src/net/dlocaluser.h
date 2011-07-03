#ifndef DLOCALUSER_H
#define DLOCALUSER_H

#include "../netex/duserex.h"

class dLocalUser: public dUserEx
{

	public:

    // Метод устанавливает себя (то есть адрес своего объекта),
    // вкачестве "главного" пользователя.
		virtual bool set_main_user();

        virtual void uptime(){};
    
    protected:    
        
    // Набор конструкторов и деструктор.
		dLocalUser(dManager * _manager, const QString &_name );
		virtual ~dLocalUser();

    // ПЕРЕГРУЖАЕМ Эхо-запрос.
		virtual void event_echo_request( dPUser _from );
    // ПЕРЕГРУЖАЕМ Info-запрос.
		virtual void event_info_request( dPUser _from );
    // ПЕРЕГРУЖАЕМ Событие, происходит при входе какого либо пользователя в чат.
		virtual void event_msg_enter( dPUser _from );
    // ПЕРЕГРУЖАЕМ Событие происходит, когда приходит запрос картинки(аватара).
		virtual void event_image_request( dPUser _from, const QString &id );
    // ПЕРЕГРУЖАЕМ Событие происходит, когда приходит личное сообщение.
		virtual void event_msg_personal( dPUser _from, const QString &_msg, bool html = false);
    // ПЕРЕГРУЖАЕМ Событие происходит, при получении массового сообщения.
		virtual void event_msg_mass( dPUser _from, const QString & _msg, bool html = false);
    // ПЕРЕГРУЖАЕМ Событие происходит ,когда приходит Xml - сообщение.
        virtual void event_xml( dPUser _from, const QDomElement &messageElement );
    
    public:
    // Возвращает тип локального пользователя...
        virtual QString get_type() const{ return tr("LOCAL_USER"); };
        
    //  Переопределим методы... в классе dUser они находятся в разделе protected,
    // то есть закрыты. Тут мы их определяем в раздел public.
		virtual bool set_name(const QString &_name){ dUserEx::set_name(_name); };
		virtual void set_host(const QString & _host){ dUserEx::set_host(_host); };
		virtual void set_login(const QString &_login){ dUserEx::set_login(_login); };
		virtual void set_version(const QString &_version){ dUserEx::set_version(_version); };
		virtual void set_percent(const QString &_percent){ dUserEx::set_percent(_percent); };
		virtual void set_memory(const QString &_memory){ dUserEx::set_memory(_memory); };
		virtual void set_sex(const uint &_sex){ dUserEx::set_sex(_sex); };
		virtual void set_auto_answer(const QString &_auto_answer){ dUserEx::set_auto_answer(_auto_answer); };
		virtual void set_topic(const QString &_topic){ dUserEx::set_topic(_topic); };
		virtual void set_mode(const uint &_mode){ dUserEx::set_mode(_mode); };
		virtual void set_activity(const bool &_activity){ dUserEx::set_activity(_activity); };
		virtual void set_avatar(const QPixmap &_avatar){ dUserEx::set_avatar(_avatar); };

    // Пергрузка методов из dUser.
    // Послать "массовое" сообщение.
		virtual void send_msg_mass( const QString & msg, dPUser _from, bool html = false );
    // Послать сообщение(личное) пользователю.
    // В качестве параметра передается указатель на объект отправителя
    // и текст сообщения.
		virtual void send_msg( const QString & msg, dPUser _from , bool html = false);
    // Послать сообщение пользователю в КАНАЛ.
		virtual void send_msg_beep( dPUser _from );
    // Послать сообщение с авто-ответом.
		virtual void send_auto_answer( dPUser _from );
		
};

#endif	//DLOCALUSER_H
