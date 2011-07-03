#include "dudpsocket.h"
Q_EXPORT_PLUGIN(dUdpSocket)
/*
#include "dwidget.h"

void dWidget::dataReceived()
{
    QHostAddress ip;
    uint port;
    char buffer[5000];
    udpSocket->readDatagram(buffer,100,&ip,&port);
    qDebug()<<tr(buffer)<<ip.toString();
};

dWidget::dWidget():QWidget()
{
    udpSocket = new dUpdSocket(this);
    qDebug() << connect(udpSocket, SIGNAL(readyRead()),
                        this, SLOT(dataReceived()));

    if( udpSocket->bind(QHostAddress(tr("1.2.3.254")),8167) )
        std::cout << "All correctly!!!" << std::endl;    

};
*/
/*
int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    dWidget * widget = new dWidget();
    widget->show();

	std::cout << "Hello world!" << std::endl;
    return app.exec();

}
*/


