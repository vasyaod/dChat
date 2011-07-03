#ifndef DSERVICE_H
#define DSERVICE_H

// Библиотеки QT.
#include <QtXml>
#include <QUdpSocket>
#include <QAbstractSocket>
#include <QTextStream>
#include <QIODevice>

#include "duser.h"

class dService;     // Описан ниже.... в этом файле.

// Абстрактный класс...
// Создан для интефейса, который должен возвращать некий список IP адресов.
class dAbstractIPList
{
    private:
        dService *service;
   
    public:
        dAbstractIPList( dService *_service = 0);
        ~dAbstractIPList();
        void addListToService( dService *_service );
        virtual const QList<QHostAddress> &get_ip_list() const= 0;
};

// Класс представляет собой диапозон IP адресов.
class dRangeIP : public dAbstractIPList
{
    private:
        QList<QHostAddress> ip_list;

    public:
        dRangeIP( const QHostAddress& _border1, 
                  const QHostAddress& _border2,
                  dService *_service = 0 );
        virtual const QList<QHostAddress> &get_ip_list() const{ return ip_list; };

};

// Класс представляет один IP адрес.
class dSingleIP : public dAbstractIPList
{
    private:
        QList<QHostAddress> ip_list;
    public:
        dSingleIP( const QHostAddress& _ip, dService *_service = 0);
        virtual const QList<QHostAddress> &get_ip_list() const{ return ip_list; };
};


class dManager;
class dRemoteUser;
class dAbstractRemoteUserCreator;
class dUdpSocket;

class dService: public QObject
{
	Q_OBJECT			// Макроопределение, нужно для работы библиотеки Qt.
	friend class dManager;
	friend class dRemoteUser;
	friend class dAbstractIPList;
    
	public:
    //***************************************************************
    // МЕТОДЫ МАССОВЫХ СООБЩЕНИЙ.
    // Тип отправки массовых сообщений.
        enum dMessageSendType
        {  
            default_type,
            list_ip_type,
            broadcast_ip_type
        };

    private:
    // Список адресов, используемой для рассылки массовых сообщений.
        QList<dAbstractIPList*> ip_lists;
        
    // Менеджер сервиса.
        dManager *manager;
    // Содержит тип отправки массовых сообщений.
        dMessageSendType send_type;
        
    // Метод создает нового удаленного пользователя.
        virtual dPUser createRemoteUser( const QHostAddress &_ip, const QString &_name );
	protected:         
                
    //***************************************************************
    // Посылает указаное сообщение на указанный IP.
		int send( const QHostAddress &_ip, const QByteArray &_msg );
        int send( const QHostAddress &_ip, const QString &_msg );

    //********* ******************************************************
    // ШАБЛОНЫ МАССОВЫХ СООБЩЕНИЙ.
    // Посылает массовый эхо-запрос.
		virtual void send_mass_echo( dMessageSendType _msg_send_type, dPUser _from );
    // Посылает массовое сообщение о ВХОДЕ пользователя в чат.
		virtual void send_mass_enter( dMessageSendType _msg_send_type, dPUser _from );
    // Посылает массовое сообщение о ВЫХОДЕ пользователя в чат.
		virtual void send_mass_exit( dMessageSendType _msg_send_type, dPUser _from );
    // Посылает сообщение в канал.
		virtual void send_mass_msg_channel( dMessageSendType _msg_send_type, dPUser _from , const QString &_msg);
    // Посылает me-стороку в канал.
		virtual void send_mass_msg_channel_me( dMessageSendType _msg_send_type, dPUser _from , const QString &_msg);
    // Посылает сообщение о смене топика.
		virtual void send_mass_change_topic( dMessageSendType _msg_send_type,  const QString &_topic);
    // Посылает сообщение о переименовании пользователя.
        virtual void send_mass_rename( dMessageSendType _msg_send_type, dPUser _from, const QString &_oldname );
    //***************************************************************
    
    // Синтаксический анализатор, который парсит XML сообщения чата.
		virtual void xmlParser( dPUser _from, dPUser _to, const QDomElement &messageElement ); 

    public:
        int useNetworkPath;
    // Метод устанавливает тип отправки массовых сообщений.
        void set_send_type( dMessageSendType _send_type ){ send_type = _send_type; };
    // Метод возвращает тип отправки массовых сообщений.
        dMessageSendType get_send_type(){ return send_type; };
    
    // Возвращает менеджера сервиса.
        dManager *get_manager(){ return manager; };
    
    // Сия определение типа, нужно для обработки исключения, 
    // вызываемого при обнаружении ошибки в работе сети.
        enum dServiceError{ init,
                            load_plugin };
        
	// Степень ведения лога.
        uint log_mode;                          

    // Набор конструкторов и деструктор.
		dService( dManager *_manager, const uint _port = 8167, uint _useNetworkPath = 0, const QHostAddress &_local_ip = QHostAddress() );
		dService( dManager *_manager, const QString &_local_ip_qstring, const uint _port = 8167, uint _useNetworkPath = 0);
		dService( dManager *_manager, dAbstractRemoteUserCreator *_absRtUsrCreator, const uint _port = 8167, uint _useNetworkPath = 0, const QHostAddress &_local_ip = QHostAddress() );
		~dService();

    // Возвращает список адресов массовой рассылки.
        virtual QList<QHostAddress> get_ip_list() const;
		
    // Изменение размера буфера в сокете. По умолчанию size = 49152.
		void setReadBufferSize( const uint size );

    //***************************************************************
    //  ФУНКЦИИ УПРАВЛЕНИЯ ЛОГОМ.
    // Вывод лога на указаное вами устройство.
		void onLog( QIODevice * _log_dev, uint _log_mode = 0xFFFFFFFF);	
    // Вывод лога в файл.
		bool onLog( const char * file_name, uint _log_mode = 0xFFFFFFFF);	
		bool onLog( const QString & file_name_qstring, uint _log_mode = 0xFFFFFFFF);
	// Создана для того чтобы выводить лог в стандартый поток (stdout).
		bool onLog( FILE * file, uint _log_mode = 0xFFFFFFFF);
    // Метод устанавливает степень ведения лога.
		void dService::setLogMode( uint _log_mode );
    // Выключает ведение лога.
		void offLog(void);						            
		
		void set_broadcast_ip( const QHostAddress &_broadcast_ip ){ broadcast_ip = _broadcast_ip; };
		
	private:
		QHostAddress	broadcast_ip;			// Содержит широковещательный адрес машины.			
		QHostAddress	localhost_ip;			// 127.0.0.1			

    // Указатель на сокет.        
		QUdpSocket      *udpSocket;         	
    // Указатель на нашь собственный класс который работает с UPD.
    // так как выеснилось их работает не правельно,
    // вернее постоянно виснет.....
        dUdpSocket      *udpSocketPath;
        
		QHostAddress	local_ip;			// Содержит локальный адрес машины.
		uint			port;				// Порт на котором открыт сервис(чат).

		QIODevice		*log_dev;			// Указатель на лог-устройство.
		QTextStream		log;				// Объект лога.

    // Указатель на абстрактный класс создателя удаленных пользователей.
        dAbstractRemoteUserCreator *absRtUsrCreator;

    // Синтаксический анализатор, который парсит сообщения чата.
    // Внутреннее использование!
		void parser( const QHostAddress &_ip, const QByteArray &_msg); 
        
    // Вызывает массовые события у всех пользователей в списке.
    // Внутреннее использование!
        void event_mass( dUser::dMsgType _event_type, dPUser _from, const QString *_msg = NULL );
    // Инициализация сокет.
    // Внутреннее использование!
        void connecting();                  
        void connectingPath();        // Тоже самое но только нашу библиотеку.
    // Вырезание тагов из текста.
    // Внутреннее использование!
        QString escapeXml( QString _xml );
													     
	private slots:
        void dataReceived();				// СЛОТ. Вызывается, когда приходят данные из сети.
        void dataReceivedPath();			// СЛОТ. Вызывается, когда приходят данные из сети.
};

#endif	//DSERVICE_H
