#include "duserinfowindow.h"

#include "../net/duser.h"

dUserInfoWindow::dUserInfoWindow( dPUser usr,QWidget *_parent ):
        QWidget(_parent)
{
 //   application = qobject_cast<dChatApplication*>(QApplication::instance());
    setWindowTitle(tr("Информация о пользователе")); 
    setWindowIcon(QIcon(tr("pic/question64x64.png"))); 
   // Востановим размеры окна.
    //resize( settingMessageEditor->toSize(tr("size"),QSize(300,200)) );        


    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(3);
        
        QHBoxLayout *infoLayout = new QHBoxLayout;
        infoLayout->setSpacing(5);
        infoLayout->setMargin(5);

        QLabel *avatarLabel = new QLabel();
        QPixmap avatar = usr->get_avatar();
        avatar.scaled(48,48);
        avatarLabel->setPixmap(avatar);
        infoLayout->addWidget( avatarLabel );
    
        QLabel *label = new QLabel(tr("<b>Имя:</b> %1<br><b>IP:</b> %2<br><b>Host:</b> %3<br><b>Login:</b> %4<br><b>Version:</b> %5")
                               .arg(usr->get_name())
                               .arg(usr->get_ip().toString())
                               .arg(usr->get_host())
                               .arg(usr->get_login())
                               .arg(usr->get_version()) );
        QFont label_font = label->font();
        label_font.setPointSize(10);
        label->setFont(label_font);
        label->setMargin(5);
        infoLayout->addWidget( label ); 
        infoLayout->addStretch ( 1 );  
    layout->addItem(infoLayout);
    
    QTextEdit * auto_answer = new QTextEdit();        
    auto_answer->setPlainText(usr->get_auto_answer());
    layout->addWidget(auto_answer);
    
        QHBoxLayout *layoutButton = new QHBoxLayout;
        layoutButton->setSpacing(5);
        QPushButton *closeButton = new QPushButton(tr("Закрыть"));
        connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
        layoutButton->addWidget( closeButton ); 
        layoutButton->addStretch ( 1 );
    
    layout->addItem(layoutButton);
    
    setLayout(layout); 
    show();
};
/*
dUserInfoWindow::~dUserInfoWindow()
{
}
*/
void dUserInfoWindow::closeEvent ( QCloseEvent * _event )
{
    QWidget::closeEvent(_event);
    delete this;
};
