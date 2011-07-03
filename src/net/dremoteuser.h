#ifndef DREMOTEUSER_H
#define DREMOTEUSER_H

#include "dabstractremoteusercreator.h"

#include "../netex/duserex.h"

class dService;

class dRemoteUser: public dUserEx
{
	friend class dService;
	friend class dRemoteUserCreator;
	
	private:
        
        QDateTime last_uptime;

    // ID таймеров.
        int timerCheckID;
        int timerInfoSendID;
    // Интервал пинга.
        int interval_ping;
        
        void send_xml_msg( const QString & _msg, dPUser _from, bool _html = true, bool mass = false );
	protected:
		dService * service;		// Указатель на сервис в котором сидит пользователь.

		dRemoteUser(dService * _service, const QHostAddress &_ip, const QString &_name );
		~dRemoteUser();
    
    // Создаем таймер и событие на его срабатывание. Для подтверждения
    // того факта, находиться ли пользователь в сети.
        virtual void timerEvent(QTimerEvent *event);

    // Обновляет время последнего упомянания о пользователе.
 		virtual void uptime();
 			
    // Функцию нужно вызвать когда нужно удалить пользователя
    // с нужным указателем на сервис.
    // Используется только 1 раз в деструкторе dService, когда
    // нужно удалить всех пользователей принадлежащих этому
    // сервису.        
        virtual void deleteRemoteUser(dService * srv);
	public:
    // Возвращает тип локального пользователя...
        virtual QString get_type() const{ return tr("REMOTE_USER"); };

    // ПЕРЕГРУЗКА ФУНКЦИЙ
    // Перегружаем операции отправки эхо-запросов.
		virtual void send_echo( dPUser _from );
		virtual void send_info_request( dPUser _from );
    // Перегружаем операции отправки эхо-ответов.
		virtual void send_info_answer( dPUser _from );
		virtual void send_echo_answer( dPUser _from );
    // Послать сообщение с авто-ответом.
		virtual void send_auto_answer( dPUser _from );
    // Послать сообщение(личное) пользователю.
		virtual void send_msg( const QString & _msg, dPUser _from, bool html = false);
    // Послать "массовое" сообщение.
		virtual void send_msg_mass( const QString & _msg, dPUser _from , bool html = false);
    // Послать запрос на передачу картинки(аватара) от пользователя.
		virtual void send_image_request( dPUser _from );
    // Послать зв. вызов от пользователя(если аргумент пустой, то сообщение 
    // посылается от имени гл. пользователя).
		virtual void send_msg_beep( dPUser _from  );
    // Сообщить о текущем топике.
		virtual void send_current_topic( const QString &_topic );
    // Смена топика.
		virtual void send_change_topic( const QString &_topic );		
    // Ответ на запрос картинки, посылает обратно аватар.
		virtual void send_image_answer( const QString &_id, dPUser _from );
    // Послать сообщение пользователю в КАНАЛ.
		virtual void send_msg_channel( const QString & msg, dPUser _from );
		virtual void send_msg_channel_me(const QString &_msg, dPUser _from );
    // Послать сообщение о изменении имени пользователя.
        virtual void send_rename( const QString &_oldname , dPUser _from );

    //***************************************************************
    // XML СООБЩЕНИЯ...
    // Послать Xml - сообщение.
        virtual void send_xml( QDomDocument &_msgXmlDocument, dPUser _from );
    // Xml ping посылается дабы узнать поддерживает ли удаленный пользователь
    // тот или иной тип протокола.
        virtual void send_xml_ping( dPUser _from );

    // Возвр. указатель на сервис удаленного пользователя .
        const dService *get_service() const { return service; };
};

class dRemoteUserCreator : public dAbstractRemoteUserCreator
{
    public:
        dRemoteUserCreator(){};
        virtual dPUser create( dService * _service, const QHostAddress &_ip, const QString &_name ) const
        {
                dRemoteUser * remoteUser = new dRemoteUser(_service,_ip,_name);
                return remoteUser->get_pointer();
        };
};

#endif	//DREMOTEUSER_H
