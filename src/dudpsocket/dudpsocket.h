#ifndef DUDPSOCKET_H
#define DUDPSOCKET_H

#include <QtGui>
#include <QHostAddress>
#include <winsock.h>

class dUdpSocket;
Q_DECLARE_INTERFACE(dUdpSocket,"dUdpSocket/1.0")

struct dBuffer
{
// Данные.
    QByteArray data;
// Адрес сокета отправителя.
    QHostAddress address;
// Порт с которого пришли данные.
    uint port;
};

class dUdpSocket : public QThread
{
    Q_OBJECT
    Q_INTERFACES(dUdpSocket)
    private:
    // Собственно сам сокет.
        SOCKET sock;
    // Классы блокировки потока.
        QMutex  mutexSend;
        QMutex  mutexRead;
        QMutex  mutexReconnect;
    // Буфер где храняться данные пришедшие с сокета.
        QByteArray buffer;
    // Набор буферов, для создания очереди.
        QList<dBuffer> outBuffers;
        QList<dBuffer> inBuffers;
    // Хранится состояние соединия.
        bool connected;
    // Размер пришедших данных.
        int datagramSize;
    
    // Параметры устанавливаются при вызове метода бинд.
        QHostAddress listen_ip;
        uint listen_port;
    public: 
        dUdpSocket(QObject * _parent = 0);
        ~dUdpSocket();
        virtual bool bind( const QHostAddress &_local_ip , uint _port );
        virtual int pendingDatagramSize() const{ return datagramSize; };
 //       virtual int readDatagram( char* _buffer, int _buffer_size, QHostAddress *_address, uint *_port );
        virtual int readDatagram( QByteArray &_datagram, QHostAddress *_address, uint *_port );
        virtual int writeDatagram ( const QByteArray & datagram, const QHostAddress & host, uint port );
        virtual int hasPendingDatagrams();
    
    protected:
        void run();
    // Тайметр.... нужен для переодического переконекчивания....
        virtual void timerEvent ( QTimerEvent * event );
        
    signals:
    // Сигнал подается, когда данные готовы к чтению.
        void readyRead();
};
#endif // DUDPSOCKET_H


