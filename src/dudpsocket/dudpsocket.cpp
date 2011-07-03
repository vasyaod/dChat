#include "dudpsocket.h"

dUdpSocket::dUdpSocket(QObject * _parent):
                QThread(_parent),
                connected(false),
                datagramSize(0)
{
    buffer.resize(65536);
 //   startTimer(1200*1000);
};

dUdpSocket::~dUdpSocket()
{
    connected = false;
    wait();
    mutexSend.unlock();
    mutexRead.unlock();
   // quit();
    closesocket(sock);
}
/*
int dUdpSocket::readDatagram(    char* _buffer,
                                 int _buffer_size,
                                 QHostAddress *_address, 
                                 uint *_port )
{

    int _datagramSize = datagramSize < _buffer_size ? datagramSize: _buffer_size;
 
    memcpy(_buffer, buffer.data(),_datagramSize);
    datagramSize = 0;
        mutex.unlock();
//    waitCondition.wakeAll();
    *_address = address;
    *_port = port;

    return _datagramSize;
};
*/

int dUdpSocket::readDatagram(   QByteArray &_datagram,
                                QHostAddress *_address, 
                                uint *_port )
{
    QMutexLocker locker(&mutexRead);
// Возмем данные из очереди.
    dBuffer _buffer = outBuffers.back();
    _datagram = _buffer.data;
    *_address = _buffer.address;
    *_port = _buffer.port;
    outBuffers.pop_back();
    
    return _datagram.size();
};

int dUdpSocket::hasPendingDatagrams()
{
    QMutexLocker locker(&mutexRead);
    return outBuffers.size();
};

int dUdpSocket::writeDatagram ( const QByteArray & _datagram, 
                                const QHostAddress & _ip, 
                                uint _port )
{
    if( !connected )
        return 0;
    QMutexLocker locker(&mutexSend);
// Добвами данные в очередь.
    dBuffer _buffer;
    _buffer.data = _datagram;
    _buffer.address = _ip;
    _buffer.port = _port;
    inBuffers.push_front(_buffer);
    
    return _datagram.size();
}

void dUdpSocket::run()
{
    int status;
    
    SOCKADDR_IN sin;
    SOCKADDR_IN sin_temp;
        
    fd_set read_s; // Множество 
    int fromlen,res;

    timeval time_out; // Таймаут чтения данных
    time_out.tv_sec = 0;
    time_out.tv_usec = 1; 

    timeval time_double_out; // Таймаут для повторного чтения
    time_double_out.tv_sec = 0;
    time_double_out.tv_usec = 1; 
    
    forever {      
     //   qDebug("++");
      //  mutexSend.lock();
        mutexReconnect.lock();        
        if( !connected && inBuffers.size() == 0 )
            return;
    //    qDebug() << inBuffers.size();
/* ================ ЧИТАЕМ ДАННЫЕ С СОКЕТА ========================== */
        
        FD_ZERO (&read_s);          // Обнуляем мнодество 
        FD_SET (sock, &read_s);     // Заносим в него наш сокет 
        res = select (0, &read_s, NULL, NULL, &time_out);
//        while ( res != 0 ) 
        if ( res != 0 && connected) 
        {       // Получаю данные }
            if (SOCKET_ERROR ==  res ) 
            {
                 qDebug("!!!+++");
                 closesocket(sock);
                 QMessageBox::critical(0, tr("Socket (select) error!"),
                                          tr("Ошибка сети. Соединение закрыто. Обращайтесь vasyaod@mail.ru"),QMessageBox::Ok,0,0);
                 qDebug("Socket (select) error!");
                 connected = false;
                 return;
            }

            fromlen = sizeof(sin);
            status = recvfrom( sock, buffer.data(), buffer.size(), 0,(struct sockaddr FAR *)&sin,&fromlen);
/* Закоментировано, из-за временной ненадобности.
            if (status == SOCKET_ERROR)
            {
                closesocket(sock);
                int error = WSAGetLastError();
                qDebug("Socket (recvfrom) error! ");
                connected = false;
                throw int(-1);
            }
*/
            if( status > 0 )
            {   
                mutexRead.lock();

                sin_temp.sin_addr.S_un.S_un_b.s_b1 = sin.sin_addr.S_un.S_un_b.s_b4;
                sin_temp.sin_addr.S_un.S_un_b.s_b2 = sin.sin_addr.S_un.S_un_b.s_b3;
                sin_temp.sin_addr.S_un.S_un_b.s_b3 = sin.sin_addr.S_un.S_un_b.s_b2;
                sin_temp.sin_addr.S_un.S_un_b.s_b4 = sin.sin_addr.S_un.S_un_b.s_b1;

                dBuffer _buffer;
                _buffer.port = sin.sin_port;
                _buffer.address.setAddress(sin_temp.sin_addr.S_un.S_addr);
                _buffer.data.resize(status);
                memcpy(_buffer.data.data(), buffer.data(),status);
                
                outBuffers.push_front(_buffer);
                mutexRead.unlock();
                emit readyRead();
            }
            
//            FD_ZERO (&read_s);          // Обнуляем мнодество 
//            FD_SET (sock, &read_s);     // Заносим в него наш сокет 
//            res = select (0, &read_s, NULL, NULL, &time_double_out);
        }

/* ================ ЗАПИСЬ ДАННЫХ В СОКЕТ ========================== */
        // Возмем данные из очереди.
        if( !inBuffers.isEmpty() )
        {
            mutexSend.lock();
            dBuffer _buffer = inBuffers.back();
            QByteArray datagram = _buffer.data;
            QHostAddress address = _buffer.address;
            uint port = _buffer.port;
            inBuffers.pop_back();
            mutexSend.unlock();

            sin_temp.sin_addr.S_un.S_addr = address.toIPv4Address();
            sin.sin_addr.S_un.S_un_b.s_b1 = sin_temp.sin_addr.S_un.S_un_b.s_b4;
            sin.sin_addr.S_un.S_un_b.s_b2 = sin_temp.sin_addr.S_un.S_un_b.s_b3;
            sin.sin_addr.S_un.S_un_b.s_b3 = sin_temp.sin_addr.S_un.S_un_b.s_b2;
            sin.sin_addr.S_un.S_un_b.s_b4 = sin_temp.sin_addr.S_un.S_un_b.s_b1;
            sin.sin_family = AF_INET;
            sin.sin_port = htons(port);
            
            status = sendto( sock, datagram.data(), datagram.size(), 0,(struct sockaddr FAR *)&sin,sizeof(sin));
            if (status == SOCKET_ERROR)
            {
                closesocket(sock);
                qDebug("Socket(sendto) error!");
                QMessageBox::critical(0, tr("Socket(sendto) error!."),
                                         tr("Ошибка сети. Соединение закрыто. Обращайтесь vasyaod@mail.ru"),QMessageBox::Ok,0,0);
                connected = false;
                return;
            }
        }
        mutexReconnect.unlock();    
    }
}

bool dUdpSocket::bind( const QHostAddress &_local_ip , uint _port)
{
   listen_ip = _local_ip;
   listen_port = _port;
  //  QMutexLocker locker(&mutex);
    if( connected )         
        closesocket(sock);       // Соединение уже установлено, закроеm его.
        
    PHOSTENT phe;
    WSADATA WSAData;
    char szTemp[80];
    int status;            

    if ((status = WSAStartup(MAKEWORD(1,1), &WSAData)) == 0) {
        qDebug() <<  tr("%1 %2").arg(WSAData.szDescription).arg(WSAData.szSystemStatus);
    }
    else {
        qDebug() <<  tr("%1 is the err").arg(status);
        return false;
    }
    
    sock = ::socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) {
        qDebug("Socket(socket) failed.");
        closesocket(sock);
        return false;
    }

    SOCKADDR_IN local_sin;
    SOCKADDR_IN local_sin_temp;
   
    local_sin_temp.sin_addr.S_un.S_addr = _local_ip.toIPv4Address();
    local_sin.sin_addr.S_un.S_un_b.s_b1 = local_sin_temp.sin_addr.S_un.S_un_b.s_b4;
    local_sin.sin_addr.S_un.S_un_b.s_b2 = local_sin_temp.sin_addr.S_un.S_un_b.s_b3;
    local_sin.sin_addr.S_un.S_un_b.s_b3 = local_sin_temp.sin_addr.S_un.S_un_b.s_b2;
    local_sin.sin_addr.S_un.S_un_b.s_b4 = local_sin_temp.sin_addr.S_un.S_un_b.s_b1;
   
    local_sin.sin_family = AF_INET;
    local_sin.sin_port = htons(_port);
   // local_sin.sin_addr.s_addr = INADDR_ANY;

    if (::bind( sock, (struct sockaddr FAR *) &local_sin, sizeof(local_sin)) == SOCKET_ERROR) {
        qDebug("Bind(sock) failed.");
        closesocket(sock);
        return false;
    }

    connected = true;
    start();
    return true;
};

void dUdpSocket::timerEvent ( QTimerEvent * event )
{
    if( connected )
    {
        QMutexLocker locker(&mutexReconnect);
        closesocket(sock);
        sleep(10);
        if( !bind(listen_ip,listen_port) )
        {
            QMessageBox::critical(0, tr("Socket(reconnect) error!."),
                                     tr("Ошибка при реконекте. Соединение закрыто. Обращайтесь vasyaod@mail.ru"),QMessageBox::Ok,0,0);
            connected = false;
            return;
        }        
    }
}

