#include "dremoteuser.h"
#include "dservice.h"
#include "dmanager.h"

dRemoteUser::dRemoteUser( dService * _service, 
						  const QHostAddress &_ip, 
						  const QString &_name ):
		dUserEx(_service->get_manager(),_ip,_name),
		service(_service)
{   /* -- ПУСТО -- */ 
    set_avatar(QPixmap(tr("avatar/noavatar.png")));

	// Отправим Инфо-запрос от имени основного пользователя.
	last_uptime = QDateTime::currentDateTime(); 
    timerCheckID    = startTimer(30000);
    interval_ping   = get_manager()->get_interval_ping();
    timerInfoSendID = startTimer(interval_ping*1000);
    QTextStream in(stdout);
    
   // in << "New remoute user:" << _ip.toString() << _name << endl;
    send_info_request(get_manager()->get_main_user());	
    send_image_request(get_manager()->get_main_user());
    send_xml_ping(get_manager()->get_main_user());
};

void dRemoteUser::deleteRemoteUser( dService * _srv )
{
    if ( get_service() ==  _srv )
        delete this;
}

dRemoteUser::~dRemoteUser()
{
    QTextStream in(stdout);
  //  in << "DELETE remoute user:" << get_ip().toString() << get_name() << endl;    
};

void dRemoteUser::send_echo_answer( dPUser _from )
{
    // Если чат поддерживает XML протакол, то отправляем сообщение
    // в виде XML.
    if( get_xml_protocol() >= 1 )
    {
        QDomDocument msgXmlDocument;
        QDomElement rootElement = msgXmlDocument.createElement(tr("messages"));
        msgXmlDocument.appendChild(rootElement);
            QDomElement echoElement = msgXmlDocument.createElement(tr("echo"));
            rootElement.appendChild(echoElement);

                QDomElement versionElement = msgXmlDocument.createElement(tr("version"));
                echoElement.appendChild(versionElement);
                QDomText version = msgXmlDocument.createTextNode(QString().setNum(_from->get_xml_protocol()));
                versionElement.appendChild(version);

                QDomElement autoAnswerElement = msgXmlDocument.createElement(tr("auto_answer"));
                echoElement.appendChild(autoAnswerElement);
                QDomText autoAnswer = msgXmlDocument.createTextNode(_from->get_auto_answer());
                autoAnswerElement.appendChild(autoAnswer);
        
                QDomElement hostElement = msgXmlDocument.createElement(tr("host"));
                echoElement.appendChild(hostElement);
                QDomText host = msgXmlDocument.createTextNode(_from->get_host());
                hostElement.appendChild(host);

                QDomElement loginElement = msgXmlDocument.createElement(tr("login"));
                echoElement.appendChild(loginElement);
                QDomText login = msgXmlDocument.createTextNode(_from->get_login());
                loginElement.appendChild(login);

                QDomElement chatVersionElement = msgXmlDocument.createElement(tr("chat_version"));
                echoElement.appendChild(chatVersionElement);
                QDomText chatVersion = msgXmlDocument.createTextNode(_from->get_version());
                chatVersionElement.appendChild(chatVersion);

                QDomElement modeElement = msgXmlDocument.createElement(tr("mode"));
                echoElement.appendChild(modeElement);
                QDomText mode = msgXmlDocument.createTextNode( QString().setNum(_from->get_mode()));
                modeElement.appendChild(mode);
                
                QDomElement activityElement = msgXmlDocument.createElement(tr("activity"));
                echoElement.appendChild(activityElement);
                QDomText activity = msgXmlDocument.createTextNode( QString().setNum((int)_from->get_activity()));
                activityElement.appendChild(activity);

                QDomElement sexElement = msgXmlDocument.createElement(tr("sex"));
                echoElement.appendChild(sexElement);
                QDomText sex = msgXmlDocument.createTextNode( QString().setNum(_from->get_sex()));
                sexElement.appendChild(sex);
        send_xml(msgXmlDocument,_from);
    }
    else
    {
        QString msg;
        QTextStream in( &msg, QIODevice::WriteOnly );
        
        in <<"1"<<get_name()<<'\x00'<<_from->get_name()<<'\x00'
           <<_from->get_mode()<<_from->get_activity()<<'\x00'
           <<_from->get_host()<<'\x00'<<_from->get_login()<<'\x00'
           <<_from->get_version()<<'\x00';
    
        service->send(get_ip(),msg);
    }
};
void dRemoteUser::send_info_answer( dPUser _from )
{
 
	QString msg;
	QTextStream in( &msg, QIODevice::WriteOnly );

	in << "G"<<get_name()<<'\x00'<<_from->get_name()<<'\x00'
	   << _from->get_host()<<'\x00'<<_from->get_login()<<'\x00'
	   << _from->get_percent() << '\x00'<< _from->get_memory() << '\x00'
	   << "#main#" << '\x00'
	   << _from->get_auto_answer()<<'\x00';

	service->send(get_ip(),msg);
};
void dRemoteUser::send_echo( dPUser _from )
{
    // Если чат поддерживает XML протакол, то отправляем сообщение
    // в виде XML.
    if( get_xml_protocol() >= 1 )
        send_xml_ping(_from);
    else
    {
        QString msg;
        QTextStream in( &msg, QIODevice::WriteOnly );
        
        in <<"0"<<_from->get_name()<<'\x00';
        service->send(get_ip(),msg);
    }
};
void dRemoteUser::send_info_request( dPUser _from )
{

	QString msg;
	QTextStream in( &msg, QIODevice::WriteOnly );

	in <<"F"<<get_name()<<'\x00'<<_from->get_name()<<'\x00';
	service->send(get_ip(),msg);
};
void dRemoteUser::send_auto_answer(  dPUser _from )
{
	QString msg;
	QTextStream in( &msg, QIODevice::WriteOnly );

	in << "7"<<_from->get_mode()<<get_name()<<'\x00' 
       << _from->get_name()<<'\x00'<<_from->get_sex()
       << _from->get_auto_answer()<<'\x00';

	service->send(get_ip(),msg);
};
void dRemoteUser::send_msg( const QString & _msg, dPUser _from, bool _html)
{
    QString msg_temp = _msg;
    msg_temp.replace(QChar(10),tr("\x0D")+tr("\x0A"));

    if( get_xml_protocol() >= 1 )
        send_xml_msg(msg_temp,_from,_html);
    else
    {    
        QString msg;
        QTextStream in( &msg, QIODevice::WriteOnly );
    
        in << "6"<<_from->get_name()<< '\x00' <<get_name()<<'\x00' << msg_temp;
        service->send(get_ip(),msg);
    }
    get_manager()->event_msg_personal(_from,get_pointer(),_msg,_html);
};

void dRemoteUser::send_msg_mass( const QString & _msg, dPUser _from, bool _html)
{
    QString msg_temp = _msg;
    msg_temp.replace(QChar(10),tr("\x0D")+tr("\x0A"));
    
    if( get_xml_protocol() >= 1 )
        send_xml_msg(msg_temp,_from,_html,true);
    else
    {
        QString msg;
        QTextStream in( &msg, QIODevice::WriteOnly );
    
        in << "E"<<_from->get_name()<< '\x00' <<get_name()<<'\x00' << msg_temp;
        service->send(get_ip(),msg);
    }
};

void dRemoteUser::send_msg_channel( const QString & _msg, dPUser _from)
{
	QString msg;
	QTextStream in( &msg, QIODevice::WriteOnly );
	in <<"2#Main"<<'\x00'<<_from->get_name()<<'\x00'<<_msg<<'\x00';
    service->send(get_ip(),msg);
};

void dRemoteUser::send_msg_channel_me( const QString & _msg, dPUser _from)
{
	QString msg;
	QTextStream in( &msg, QIODevice::WriteOnly );
	in <<"A#Main"<<'\x00'<<_from->get_name()<<'\x00'<<_msg<<'\x00';
    service->send(get_ip(),msg);
};

void dRemoteUser::send_rename( const QString &_oldname , dPUser _from )
{
	QString msg;
	QTextStream in( &msg, QIODevice::WriteOnly );
    in <<"3"<<_oldname<<'\x00'<<_from->get_name();
    service->send(get_ip(),msg);
};


void dRemoteUser::send_image_request( dPUser _from )
{
	QString msg;
	QTextStream in( &msg, QIODevice::WriteOnly );

	in << "IMGREQ"<<'\x00' << "1234567";
	service->send(get_ip(),msg);
};

void dRemoteUser::send_msg_beep( dPUser _from )
{
	QString msg;
	QTextStream in( &msg, QIODevice::WriteOnly );

	in << "H0"<<get_name() <<'\x00' << _from->get_name();
	service->send(get_ip(),msg);
};

void dRemoteUser::send_current_topic( const QString &_topic )
{
	QString msg;
	QTextStream in( &msg, QIODevice::WriteOnly );

	in << "C"<<get_name() <<'\x00' << _topic;
	service->send(get_ip(),msg);
}

void dRemoteUser::send_change_topic( const QString &_topic )
{
	QString msg;
	QTextStream in( &msg, QIODevice::WriteOnly );

	in << "B"<<_topic <<'\x00';
	service->send(get_ip(),msg);
}

void dRemoteUser::send_image_answer( const QString &_id, dPUser _from )
{
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);    
    if ( _from->get_avatar().save(&buffer, "PNG") )
    {
        QString msg;
        QTextStream in( &msg, QIODevice::WriteOnly );
        in << "IMGOUT"<<'\x00'<<_from->get_name()<<'\x00'<<_id <<'\x00';
        QByteArray msg_data = msg.toLocal8Bit();
        service->send( get_ip(), msg_data + bytes);
    }
};

//***********************************************************************
//
//                          XML СООБЩЕНИЯ
//

void dRemoteUser::send_xml( QDomDocument &_msgXmlDocument, dPUser _from )
{
    QDomElement rootElement = _msgXmlDocument.documentElement();
    if ( rootElement.tagName() != tr("messages") )
        return;
   
    QDomElement messageElement = rootElement.firstChildElement();
    while (!messageElement.isNull()) 
    {        
        QDomElement fromElement = _msgXmlDocument.createElement(tr("from"));
        messageElement.appendChild(fromElement);
        fromElement.setAttribute(tr("name"),_from->get_name());
        fromElement.setAttribute(tr("ip"),_from->get_ip().toString());
    
        QDomElement toElement = _msgXmlDocument.createElement(tr("to"));
        messageElement.appendChild(toElement);
        toElement.setAttribute(tr("name"),get_name());
        toElement.setAttribute(tr("ip"),get_ip().toString());
    
        messageElement = messageElement.nextSiblingElement();
    }       
    
    QString msg;
    QTextStream in( &msg, QIODevice::WriteOnly );
    _msgXmlDocument.save( in, 3 );
	service->send(get_ip(),msg);
};

void dRemoteUser::send_xml_ping( dPUser _from )
{
    QDomDocument msgXmlDocument;
    QDomElement rootElement = msgXmlDocument.createElement(tr("messages"));
    msgXmlDocument.appendChild(rootElement);
        QDomElement pingElement = msgXmlDocument.createElement(tr("ping"));
        rootElement.appendChild(pingElement);
            QDomElement versionElement = msgXmlDocument.createElement(tr("version"));
            pingElement.appendChild(versionElement);
            QDomText version = msgXmlDocument.createTextNode(QString().setNum(_from->get_xml_protocol()));
            versionElement.appendChild(version);
    
    send_xml(msgXmlDocument,_from);
};

void dRemoteUser::send_xml_msg( const QString & _msg, dPUser _from, bool _html , bool _mass )
{
    QDomDocument msgXmlDocument;
    QDomElement rootElement = msgXmlDocument.createElement(tr("messages"));
    msgXmlDocument.appendChild(rootElement);
        QDomElement pingElement = msgXmlDocument.createElement(tr("message"));
        rootElement.appendChild(pingElement);

            QDomElement dataElement = msgXmlDocument.createElement(tr("data"));
            dataElement.setAttribute(tr("type"), _html? tr("html") : tr("text"));
            pingElement.appendChild(dataElement);
            QDomText text = msgXmlDocument.createTextNode(_msg);
            dataElement.appendChild(text);
    
            QDomElement typeElement = msgXmlDocument.createElement(tr("message_type"));
            pingElement.appendChild(typeElement);
            QDomText type = msgXmlDocument.createTextNode( _mass? tr("mass") : tr("personal") );
            typeElement.appendChild(type);
        
        //------------------------------------------------------
        // Совместимость с предыдущими версиями... Ver <= 1.0.3
            typeElement = msgXmlDocument.createElement(tr("type"));
            pingElement.appendChild(typeElement);
            type = msgXmlDocument.createTextNode( _mass? tr("mass") : tr("personal") );
            typeElement.appendChild(type);
        //------------------------------------------------------

    send_xml(msgXmlDocument,_from);
};

//***************************************************************
//  Cобытие на срабатывание таймера. Для подтверждения
// того факта, находиться ли пользователь в сети.
void dRemoteUser::timerEvent( QTimerEvent *event )
{
    if ( event->timerId() == timerCheckID )
    {
        QDateTime _time = last_uptime.addSecs(get_manager()->get_timeout());
        if( QDateTime::currentDateTime() >= _time )
        {
            killTimer(timerCheckID);
            killTimer(timerInfoSendID);
            killTimer(timerInfoSendID);
            delete this;
            return;
        }
        else if( service->get_send_type() == dService::broadcast_ip_type )
            send_echo(get_main_user());
            
        if( interval_ping != get_manager()->get_interval_ping())
        {
            interval_ping = get_manager()->get_interval_ping();
            killTimer(timerInfoSendID);
            timerInfoSendID = startTimer(interval_ping*1000);
        }
    }
    if ( event->timerId() == timerInfoSendID )
    {
        send_info_request(get_main_user());	
        send_image_request(get_main_user());	
    }
}
//***************************************************************
// Обновляет время последнего упомянания о пользователе.
void dRemoteUser::uptime()
{
	last_uptime = QDateTime::currentDateTime(); 
};	

