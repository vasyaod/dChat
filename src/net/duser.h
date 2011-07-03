#ifndef DUSER_H
#define DUSER_H

// Библиотеки QT
#include <QtXml>
#include <QObject>
#include <QString>
#include <QHostAddress>
#include <QPixmap>
#include <QDateTime>
#include <QMetaType>
// Стандартные библиотеки С++. 
// #include <iostream.h>

class dManager;
class dService;
class dUser;

// Создаем интелектуальный указтель на обьект dUser
class dPUser
{
    friend class dUser;
//    friend class dManager;
    private:
        dManager *manager;
        dUser *user;
    protected:
        dPUser( dManager *_manager, dUser *_user );
        dPUser( dUser *_user );

        operator dUser*();
    public:
        dPUser():user(NULL),manager(NULL){};
    // Перегрузим конструктор копии.
        dPUser( const dPUser &_user );
    // Перегрузим оператор присваивания.
        dPUser & operator= ( const dPUser &_user );

    // Перегрузим оператор, который возвращает указатель на нужный нам обект.
        virtual dUser*operator->();
        
    // Метод возвращает указатель на главного польльзователя.
        static dPUser main_user( dManager *_manager );
     //   static dPUser main_user( dManager *_manager );
     //   dPUser main_user();
   /*             
        operator bool()
        { 
            return (user == NULL && manager == NULL) ? true: false;
        };       
   */
        bool operator == ( bool b )
        { 
            if( b )
                return (user == NULL || manager == NULL) ? false: true;
            return (user == NULL || manager == NULL) ? true: false;
        }; 
            
        bool operator == ( const dPUser &usr)
        { 
            return (usr.user == user) ? true: false;
        };   
       
        bool operator !()
        { 
            return (user == NULL || manager == NULL) ? true:false;
        };

};

class dUser : public QObject
{
    friend class dService;
    
    private:
//--------------------------------------------------------------
// Свойства пользователя чата.
		QString	login;		// Логим под которым он защел на компьютер.
		QString	host;		// Имя компьютера.
		QString	version;	// Версия чата.
		QString	auto_answer;// Авто-ответ.

		uint	sex;		// Пол.
		QString	memory;		// Количество памяти на компьютере.
		QString	percent;	// Процент загруженности системы.
		QString	topic;		// Заголовок в чате.
        bool	activity;   // Активность пользавтеля: (1 - активен, 0 - неактивен)
        uint	mode;       // Активность пользавтеля: (0 - нормальный, 1 - DND, 2 - Avay, 3 - Offline)
        QPixmap	avatar;     // Картинка.
        uint xml_protocol;   // Версия XML протакола.
        QHash<QString,QVariant> property; // Дополнительные свойства пользователя,
                                         // созданы для расширения.
//--------------------------------------------------------------
//    Основные параметры, которые отделяют одного пользователя от
// другого, это адрес машины, и имя пользователя.

		QString	 name;		    // Имя(nickname)
		QHostAddress ip;		// IP-адресс
								// который является сервером этого объекта.

        // Устарело...
		// QDateTime time;			// Время последнего упоменания о пользователе.

		dManager	* manager;		// Ссылка указатель на класс dManager,
    protected:
    
    //***************************************************************
    // Установка свойств пользователя.
        
		virtual bool set_name(const QString &_name)       { name  =_name; return true;};
    //  Отключена за ненадобностью.  
    //  virtual void set_ip(const QHostAddress & _ip)     { ip    =_ip; };
		virtual void set_host(const QString & _host)      { host  =_host; };
		virtual void set_login(const QString &_login)     { login =_login; };
		virtual void set_version(const QString &_version) { version =_version; };
		virtual void set_percent(const QString &_percent) { percent =_percent; };
		virtual void set_memory(const QString &_memory)   { memory =_memory; };
		virtual void set_sex(const uint &_sex)            { sex   =_sex; };
		virtual void set_auto_answer(const QString &_auto_answer){  auto_answer=_auto_answer; };
		virtual void set_mode(const uint &_mode)          { mode =_mode; };
		virtual void set_activity(const bool &_activity)  {activity=_activity; };
		virtual void set_avatar(const QPixmap &_avatar)   { avatar =_avatar; };
		virtual void set_xml_protocol(uint _xml_protocol) { xml_protocol =_xml_protocol; };    
    public:
		virtual void set_property(const QString &key, const QVariant &value) 
                                                          { property.insert(key, value); };    
		virtual void set_topic(const QString &_topic)     { topic =_topic; };    
    protected:
    // Обновляет время последнего упомянания о пользователе.
 		virtual void uptime(){};
    // Функцию нужно вызвать когда нужно удалить пользователя
    // с нужным указателем на сервис.
    // Используется только 1 раз в деструкторе dService, когда
    // нужно удалить всех пользователей принадлежащих этому
    // сервису.
        virtual void deleteRemoteUser(dService * srv){};
        
	public:
	// Метод просто удаляет текущий объект, вызывая деструктор.
        void delete_user(){ delete this; };
        
	// Возвращает интелектуальный указтель на текущий объект.
       dPUser get_pointer();

    // Метод устанавливает главного пользователя от имени которого работает
    // чат. 
		virtual bool set_main_user(){ return false; };
    // Возвращает главного пользователя.
		virtual dPUser get_main_user()const;

    // Проверка на превышение времени молчания, если время выходит,
    // то пользователь удаляется из памяти.	
	//	virtual void check_time_out();	
        
    //***************************************************************
	// Получение свойств пользователя.
		virtual const QHostAddress &get_ip()    const{ return ip; };
		virtual const QString &get_name()       const{ return name; };
		virtual const QString &get_host()       const{ return host; };
		virtual const QString &get_login()      const{ return login; };
		virtual const QString &get_version()    const{ return version; };
		virtual const QString &get_percent()    const{ return percent; };
		virtual const QString &get_memory()     const{ return memory; };
		virtual uint           get_sex()        const{ return sex; };
		virtual const QString &get_auto_answer()const{ return auto_answer; };
		virtual const QString &get_topic()      const{ return topic; };
		virtual uint           get_mode()       const{ return mode; };
		virtual bool           get_activity()   const{ return activity; };
		virtual const QPixmap &get_avatar()     const{ return avatar; };
		virtual uint           get_xml_protocol()const{ return xml_protocol; };    
        virtual       QVariant  get_property(const QString &key ){ return property.value(key); };
        virtual const QHash<QString,QVariant> &get_properties(){ return property; };
		virtual QPixmap        avatarToPixmap() const{ return avatar; };

    // Возвращает тип локального пользователя...
        virtual QString get_type() const{ return tr("USER"); };

    // Возвращает указатель на менеджера пользо(dManager).
		virtual dManager *get_manager()        const{ return manager; };
            
    // Конструктор и деструктор.
		dUser( dManager * _manager, const QHostAddress &_ip, const QString &_name);
		virtual ~dUser();

    // Перезагрузим оператор равенства, два объета qUser равны,
    // когда у них равны инена и Ip.
		int operator== (dUser &usr); 

    // Послать Info и Echo - запросы для пользователя.
    // В качестве параметра передается указатель на объект отправитеь.
		virtual void send_info_request( dPUser _from ){};
		virtual void send_echo( dPUser _from ){};
    // Послать запрос на передачу картинки(аватара) от пользователя.
		virtual void send_image_request( dPUser _from ){};
    // Ответ на запрос картинки, посылает обратно аватар.
		virtual void send_image_answer( const QString &_id, dPUser _from ){};
    // Послать Info и Echo - ответы для пользователя.
    // В качестве параметра передается указатель на объект отправитеь.
		virtual void send_info_answer( dPUser _from ){};
		virtual void send_echo_answer( dPUser _from ){};
    // Послать сообщение с авто-ответом.
		virtual void send_auto_answer( dPUser _from ){};
    // Послать сообщение(личное) пользователю.
    // В качестве параметра передается указатель на объект отправителя
    // и текст сообщения.
		virtual void send_msg( const QString & msg, dPUser _from, bool html = false ){};
    // Послать сообщение пользователю в КАНАЛ.
		virtual void send_msg_channel( const QString & msg, dPUser _from ){};
		virtual void send_msg_channel_me(const QString &_msg, dPUser _from ){};	
    // Послать звуковой сигнал пользователю.
		virtual void send_msg_beep( dPUser _from ){};
    // Послать "массовое" сообщение.
		virtual void send_msg_mass( const QString & msg, dPUser _from, bool html = false ){};
    // Сообщить о текущем топике.
		virtual void send_current_topic( const QString &_topic ){};
    // Смена топика.
		virtual void send_change_topic( const QString &_topic ){};
    // Послать сообщение о изменении имени пользователя.
        virtual void send_rename( const QString &_oldname , dPUser _from ){};

    //***************************************************************
    // XML СООБЩЕНИЯ...
    // Послать Xml - сообщение.
        virtual void send_xml( QDomDocument &_msgXmlDocument, dPUser _from ){};
    // Xml ping посылается дабы узнать поддерживает ли удаленный пользователь
    // тот или иной тип протокола.
        virtual void send_xml_ping( dPUser _from ){};
        
    //***************************************************************
    // ТИПЫ СООБЩЕНИЙ.
        enum dMsgType
        {
            echo_answer         = 1,        
            info_answer         = 2,        
            info_request        = 4,
            echo_request        = 8,
            change_activity     = 16,
            change_mode         = 32,
            msg_personal        = 64,
            msg_channel         = 128,
            msg_beep            = 256,
            msg_mass            = 512,
            change_topic        = 1024,
            current_topic       = 2048,
            msg_channel_me      = 4096,
            msg_enter           = 8192,
            msg_exit            = 16384,
            msg_rename          = 32768,
            msg_beep_answer     = 65536,       
            msg_auto_answer     = 131072,       
            image_request       = 262144,
            image_answer        = 524288,
            msg_xml             = 1048576,
            msg_all             = 0xFFFFFFFF       
        };
    
    protected:
    //***************************************************************
    //  СОБЫТИЯ, КОТОРЫЕ ВЫЗЫВАЮТСЯ ПРИ ПОЛУЧЕНИИ ОПРЕДЕЛЕННЫХ
    // СООБЩЕНИЙ.
        
    // Обобщеный метод, который вызывается при появлении всех событий,
    // только, с различным параметром _event_type.
		virtual void event( dMsgType _event_type, dPUser _from, const QString *_msg = NULL){};

	// Далее идут частные случаи, приведенной выше функции.
    // Событие происходит, при получении info-запроса.
		virtual void event_info_request( dPUser _from ){};
    // Событие происходит, при получении echo-запроса.
		virtual void event_echo_request( dPUser _from ){};
    // Событие происходит при смене активности.
		virtual void event_change_activity( dPUser _from ){};
    // Событие происходит при смене режима.
		virtual void event_change_mode( dPUser _from ){};
    // Событие происходит, при входе какого либо пользователя в чат.
		virtual void event_msg_enter( dPUser _from ){};
    // Событие происходит, при выходе пользователя из чата.
		virtual void event_msg_exit( dPUser _from ){};
    // Событие происходит, при выходе пользователя из чата.
		virtual void event_msg_rename( dPUser _from ){};
    // Событие происходит, когда приходит личное сообщение.
		virtual void event_msg_personal( dPUser _from, const QString & _msg, bool html = false){};
    // Событие происходит, когда приходит сообщение в канал.
		virtual void event_msg_channel( dPUser _from, const QString & _msg){};
    // Событие происходит, когда приходит звуковой сигнал.
		virtual void event_msg_beep( dPUser _from ){};
    // Событие происходит, при получении массового сообщения.
		virtual void event_msg_mass( dPUser _from, const QString & _msg, bool html = false){};
    // Событие происходит, при получении авто-ответа.
		virtual void event_msg_auto_answer( dPUser _from, const QString & _msg){};
    // Событие происходит, при смене топика.
		virtual void event_change_topic( const QString &_topic ){};
    // Событие происходит, когда приходит сообщение с текущим топиком.
		virtual void event_current_topic( const QString &_topic){};
    // Событие происходит, когда приходит сообщение в канал с пометкой 
    // шепнуть (Me-сообщения).event_change_topic
		virtual void event_msg_channel_me( dPUser _from, const QString & msg){};
    // Событие происходит, когда приходит запрос картинки(аватара).
		virtual void event_image_request( dPUser _from, const QString &id ){};
    // Событие происходит, новая картинка(аватар) от пользователя.
		virtual void event_image_answer( dPUser _from ){};
    // Событие происходит, Xml - сообщение.
        virtual void event_xml( dPUser _from, const QDomElement &messageElement ){};

};

Q_DECLARE_METATYPE(dPUser)

#endif	//DUSER_H

