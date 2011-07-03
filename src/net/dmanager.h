#ifndef DMANAGER_H
#define DMANAGER_H

// Библиотеки Qt4.
#include <QList>
#include <QHostAddress>

// Стандартные библиотеки С++. 
#include <list>

#include "duser.h"
#include "dservice.h"

class dChatApplication;
class QStandardItemModel;
class QItemSelectionModel;

class dManager : public QObject
{
    // Обьявим друзей класса.
	friend dService::~dService();
	friend dService::dService(  dManager *_manager,
                                const uint _port,
                                uint _useNetworkPath,
                                const QHostAddress &_local_ip );
	friend dService::dService(  dManager *_manager,
                                dAbstractRemoteUserCreator *_absRtUsrCreator, 
                                const uint _port,
                                uint _useNetworkPath,
                                const QHostAddress &_local_ip );
	friend dService::dService(  dManager *_manager,
                                const QString &_local_ip_qstring,
                                const uint _port, 
                                uint _useNetworkPath );
	friend void dService::connecting();
	
	friend dUser::~dUser();
    friend dUser::dUser( dManager * _manager, 
                         const QHostAddress &_ip, 
                         const QString &_name );
    friend class dPUser;
    
	private:
    // Интервал времени в секундах, через который происходит ехо-опрос всех пользователей
    // чата, то есть время, через которое, посылаеются массовые ехо-запросы.
    // по умолчанию 60 сек.
        uint interval_refresh;

    // Интервал времени в секундах, через который посылается пинг пользователю,
    // дабы определить его активность.
    // по умолчанию 40 сек.
        uint interval_ping;
        
    // Время жизни не активного пользователя( по умолчанию 150 сек).
        uint timeout;
        
	// Список всех сервисов, то есть чатов, их может быть несколько,
	// на разных портах.
		QList<dService*> services;
    // Список всех юзеров, которые находятся на всех сервисах(чатах),
    // в том числе и локальных.
		QList<dUser*> users;	

    // Указатель на "основного" пользователя.
		dPUser main_user;		
    // Указатель на главный объект приложения.
        dChatApplication *application;

    // Локальный адрес машины.
        QHostAddress localIP;
            
    // Номер таймера обновления списка.
        int refreshTimerID;
    protected:		
    // Событие таймера.
        void timerEvent(QTimerEvent *event);
    
    // Устанавливает локальный адрес машины.
    //    void set_localAddress( const QHostAddress &_localIP ){ localIP = _localIP; };
        
    //***************************************************************
    // Методы добавляют(удаляют) сервис в список(из списка).
	// Используются в конструкторе и деструкторе класса dService.
    // То есть, объекты класса dService, при создании сами добавляют(удаляют)
	// себя в список.
		virtual void deleteService(dService * service);
		virtual dService *addService(dService * service);
    
    //***************************************************************
    // Методы добавляют(удаляют) пользователя в список(из списка).
    // При этом происходит проверка на дублирование.
		virtual dUser *addUser(dUser * usr);
		virtual void deleteUser(dUser * usr);		
    
    public:
      
    // Получить локальный адрес машины.
        QHostAddress get_localAddress() const{ return localIP; };

    // Методы возвращают и устанавливают Время жизни не активного пользователя, 
    // время которое может жить удаленный поьзователь и не отвечать на эхо-запросы.
        uint get_timeout() const{ return timeout; };
        void set_timeout( uint _timeout ){ timeout = _timeout; };

    // Методы возвращают и устанавливают интервал посылания пинга
    // пользователю для проверки его активности. 
        uint get_interval_ping() const{ return interval_ping; };
        void set_interval_ping( uint _interval_ping ){ interval_ping = _interval_ping; };

    // Методы возвращают и устанавливают интервал времени через
    // корое идут массовые эхо запросы.
        uint get_interval_refresh() const{ return interval_refresh; };
        void set_interval_refresh( uint _interval_refresh );
		
    // Возврат указателя на основного пользователя.
		virtual dPUser get_main_user() const { return main_user; };
    // Ставит гл. пользователя.(текущего)
        virtual void set_main_user( dPUser _usr ){ main_user = _usr; };
		        
    // Возвращает количество пользователей в списке.
		uint get_user_count() const;
		
    // Поиск пользователя в списке по его IP и Имени.
		virtual dPUser find_user( const QHostAddress &_ip, const QString &_name);
		virtual dPUser find_user( const QString & _ip, const QString &_name);
		virtual dPUser find_user( const char * _ip, const char * _name);
    // Поиск пользователей по IP-адресу.
		virtual QList<dPUser> find_users_by_ip( const QHostAddress &_ip );
    
    // Дает возможность получить списки пользователей или сервисов
    // но возможность их изменения отсутствует.
		virtual QList<dPUser> get_users() const;
		virtual const QList<dService*>& get_services() const { return services; };

    // Конструктор и деструктор.
		dManager( QObject  *_parent = 0 );
		~dManager();
        
    // Виды массовых сообщений.
        enum dMessageMassType
        {  
            msg_echo,
            msg_enter,
            msg_exit,
            msg_channel,
            msg_channel_me,
            msg_mass,
            msg_rename,
            change_topic
        };
    // Обобщенный метод отправки массовых сообщений.
		bool send_mass( dService::dMessageSendType _msg_send_type,
                        dMessageMassType _msg_mass_type, 
                        dPUser _from = dPUser(), 
                        const QString* _msg = NULL );    
    // Далее идут методы, которые просто вызывают описанный выше метод
    // с различным параметором _msg_type.
    // Посылает массовый эхо-запрос от имени "основаного" пользователя,
		bool send_mass_echo( dService::dMessageSendType _msg_send_type  = dService::default_type );
    // Посылает массовае сообщение о ВХОДЕ пользователя в чат.
		void send_mass_enter( dPUser _from = dPUser(), dService::dMessageSendType _msg_send_type = dService::default_type );
    // Посылает массовае сообщение о ВЫХОДЕ пользователя в чат.
		void send_mass_exit( dPUser _from = dPUser(), dService::dMessageSendType _msg_send_type = dService::default_type);	

/*======================================================================
        УСТАРЕЛО.... В ДАННЫЙ МОМЕТ НЕ ИСПОЛЬЗУЕТСЯ...
    // Посылает массовае сообщение в канал.
		void send_mass_msg_channel( const QString &_msg, dUser *_from = 0, dService::dMessageSendType _msg_send_type = dService::default_type );	
    // Посылает массовае сообщение в канал.
		void send_mass_msg_channel_me(const QString &_msg, dUser *_from = 0,  dService::dMessageSendType _msg_send_type = dService::default_type );	
    // Послать сообщение о переименовании пользователя
        void send_mass_rename( const QString &_oldname , dUser *_from , dService::dMessageSendType _msg_send_type = dService::default_type);
    // Массовая отправка нового топика.
        void send_mass_change_topic( const QString &_topic , dService::dMessageSendType _msg_send_type = dService::default_type);
*/
    //***************************************************************
        
    // Следующие методы созданы для удобства, их описание можно найти 
    // в dUser. И созданы для отправки сообщений сразу нескольким
    // пользователям.
		bool send_info_request( const QList<dPUser> &_to, dPUser _from );
		bool send_image_request( const QList<dPUser> &_to, dPUser _from );
		bool send_msg( const QList<dPUser> &_to,const QString & msg, dPUser _from, bool _html = false);
        bool send_msg_mass( const QList<dPUser> &_to,const QString & msg, dPUser _from, bool _html = false);
		bool send_msg_beep( const QList<dPUser> &_to, dPUser _from );		
		bool send_auto_answer( const QList<dPUser> &_to, dPUser _from );
		bool send_change_topic( const QList<dPUser> &_to, const QString & _topic );
		bool send_msg_channel( const QList<dPUser> &_to,const QString & msg, dPUser _from );
		bool send_msg_channel_me( const QList<dPUser> &_to,const QString & msg, dPUser _from );
        bool send_rename( const QList<dPUser> &_to, const QString &_oldname , dPUser _from );
        
    //***************************************************************
    // Некоторые события чата.
    // Событие происходит при смене активности.
		virtual void event_change_activity( dPUser _from ){};
    // Событие происходит при смене режима.
		virtual void event_change_mode( dPUser _from ){};
    // Событие происходит, при входе какого либо пользователя в чат.
		virtual void event_msg_enter( dPUser _from ){};
    // Событие происходит, при выходе пользователя из чата.
		virtual void event_msg_exit( dPUser _from ){};
    // Событие происходит, при выходе пользователя из чата.
		virtual void event_msg_rename( dPUser _from, const QString & _oldname ){};
    // Событие происходит, когда приходит личное сообщение.
		virtual void event_msg_personal( dPUser _from, dPUser _to ,const QString & _msg, bool _html = false){};
    // Событие происходит, когда приходит сообщение в канал.
		virtual void event_msg_channel( dPUser _from, const QString & _msg){};
    // Событие происходит, когда приходит звуковой сигнал.
		virtual void event_msg_beep( dPUser _from, dPUser _to ){};
    // Событие происходит, при получении массового сообщения.
		virtual void event_msg_mass( dPUser _from, dPUser _to, const QString & _msg, bool _html = false){};
    // Событие происходит, при смене топика.
		virtual void event_change_topic( const QString &_topic ){};
    // Событие происходит, когда приходит сообщение с текущим топиком.
		virtual void event_current_topic( const QString &_topic){};
    // Событие происходит, когда приходит сообщение в канал с пометкой 
    // шепнуть (Me-сообщения).event_change_topic
		virtual void event_msg_channel_me( dPUser _from, const QString &_msg){};
    // Событие происходит, при получении авто-ответа.
		virtual void event_msg_auto_answer( dPUser _from, dPUser _to, const QString & _msg){};
    // Событие происходит ,когда приходит Xml - сообщение.
		virtual void event_xml( dPUser _from, dPUser _to, const QDomElement &messageElement ){};
    
    //***************************************************************
    //  Добавление к интерфейсу дополнительных виртуальных функция.
    // Созданы при расширении библиотеки, перегружаются в классе dManagerEx
    // Нeader file: dManagerEx.h
    // Добавлено: 08.08.2005
    public:
    // Возвращает указатель на модель данных и на 
    // модель выделения данных    
        virtual QStandardItemModel *get_model() const{ return 0; };
        virtual QItemSelectionModel *get_selectionModel() const{ return 0; };

    // Возвращает список пользователей которые выделены в модели.
        virtual QList<dPUser> getSelectedUserToModel(){ return QList<dPUser>(); };
    // Возвращает пользователя который является текущим в модели.
        virtual dPUser getCurrentUserToModel(/* QModelIndex &_index */){ return dPUser(); };

};

#endif	//DMANAGER_H

