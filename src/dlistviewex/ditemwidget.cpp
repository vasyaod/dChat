#include "ditemwidget.h"

dItemWidget::dItemWidget( QWidget *parent ):
        QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(1);
// Добавим аватар.    
    label_avatar = new QLabel();
  //  label_avatar->setMaximumSize(48,100);
    layout->addWidget(label_avatar);    
// Добавим данные о пользователе.
    label_info = new QLabel("----");// Добавим данные о пользователе.
    layout->addWidget(label_info);
    layout->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));
    setLayout(layout);    
};

void dItemWidget::set_name( QString _name )
{
    name = _name;
    set();
};

void dItemWidget::set_ip( QString _ip )
{
    ip = _ip;
    set();
};
void dItemWidget::set_host( QString _host )
{
    host = _host;
    set();
};
void dItemWidget::set_login( QString _login )
{
    login = _login;
    set();
};
void dItemWidget::set_auto_answer( QString _auto_answer )
{
    auto_answer = _auto_answer;
    set();
};   
void dItemWidget::set_version( QString _version )
{
    version  = _version;
    set();
};           
void dItemWidget::set_avatar( QIcon _avatar )
{
    label_avatar->setPixmap(_avatar.pixmap(48,48));
   // label_avatar->resize( QSize(48,48) );
};

void dItemWidget::set()
{
	QString msg;
	QTextStream in( &msg, QIODevice::WriteOnly );
    in << "<font size=\"2\">Nick:<b>"<<name<<"</b></font><font size=\"-1\"><br> IP:<b><u>"
       <<ip<<"</u></b><br>Host:<b>"<<host
       <<"</b><br>Chat:<b>"<<version<<"</b></font><br>";

	label_info->setText(msg);
};      
void dItemWidget::set_all(  const QString &_name, 
                            const QString &_ip, 
                            const QString &_host,
                            const QString &_version,
                            const QString &_login,
                            const QString &_auto_answer,
                            const QIcon   &_avatar)
{
    name = _name;
    ip = _ip;
    host = _host;
    version = _version;
    login = _login;
    auto_answer = _auto_answer;
    set_avatar(_avatar);
    set();
};

void dItemWidget::select()
{
    QPalette palette;
    palette.setColor ( QPalette::Base, selectColor );
    setPalette(palette);
    update();

};

void dItemWidget::unselect()
{
    QPalette palette;
    palette.setColor ( QPalette::Base, bgColor );
    setPalette(palette);
    update();
};
