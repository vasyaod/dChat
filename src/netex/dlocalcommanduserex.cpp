#include "dlocalcommanduserex.h"
#include "dmanagerex.h"

#include "../dchatapplication.h"
#include "../dwarningwindow/dwarningwindow.h"

Q_DECLARE_METATYPE(QProcess *);

dSettingCommandLocalUserEx::dSettingCommandLocalUserEx( dSetting *_parent,
                                                        dLocalCommandUserEx *_localCommandUserEx):
            localCommandUserEx(_localCommandUserEx),
            dSetting(tr("extended"),_parent )
{
    localCommandUserEx->set_command(get(tr("command"),tr("value"),tr("echo.bat \"test\"")));
};

QWidget *dSettingCommandLocalUserEx::createWidget()
{ 
    QWidget * widget =  new QWidget();
    
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(1);
    layout->setSpacing(5);
    
    layout->addWidget ( new QLabel(tr("Выполняемая команда, есть возможность использовать следующие переменные:\n   $ip - адрес пользователя;\n   $name - имя пользователя;\n   $host - имя машины пользователя;\n   $msg - присылаемое сообщение;")) );
    QLineEdit *commandLineEdit = new QLineEdit(localCommandUserEx->get_command());
    connect(commandLineEdit, SIGNAL(textEdited(const QString&)), this, SLOT(commandEdited(const QString&)));
    layout->addWidget ( commandLineEdit );
    
    widget->setLayout(layout); 
    
    return widget; 
};

void dSettingCommandLocalUserEx::commandEdited( const QString& _itemName)
{
    localCommandUserEx->set_command(_itemName);
    set(tr("command"),tr("value"),_itemName);
};


//***************** КОНСТРУКТОРЫ И ДЕСТРУКТОРЫ *******************
dLocalCommandUserEx::dLocalCommandUserEx(	dManagerEx * _manager, 
                            const QString &_name,
                            QDomElement &_parentXmlElement, 
                            dSetting *_parentSetting ):
            dLocalUserEx(_manager,_name,tr(COMMAND_USER_KEY),_parentXmlElement,_parentSetting)
{ 
    dSettingCommandLocalUserEx *settingCommandLocalUserEx;
    dLocalCommandUserEx *localCommandUserEx = this;
    settingCommandLocalUserEx = new dSettingCommandLocalUserEx((dSetting*)setting,(dLocalCommandUserEx *)localCommandUserEx);
    settingCommandLocalUserEx->setNode(false);
    settingCommandLocalUserEx->setTitle(tr("Настройка команд"));
};
    
dLocalCommandUserEx::~dLocalCommandUserEx()
{
    // Завершим все процессы при выходе пользователя.
    foreach( QProcess *process, processHash.keys() )
        delete process;
}

void dLocalCommandUserEx::event_msg_personal( dPUser _from, const QString & _msg, bool _html )
{
   // command = tr("run.bat");
    QProcess *process = NULL;
   // dPUser= _from;
   // QList<dPUser> user_list = processHash.keys;
    
  //  QList<dPUser> user_list = processHash.values();
  //  user_list.contains(_from);

    QHash<QProcess *, dPUser>::const_iterator i = processHash.constBegin();
    while (i != processHash.constEnd()) {
        dPUser usr =  i.value();
        if( usr == _from )
            process = i.key();
        ++i;
    }    
/*
    QHashIterator<QProcess *, dPUser> i(processHash);
    while (i.hasNext()) 
    {
        dPUser usr =  i.value();
        if( usr == _from )
            process = i.key();
    }
*/    
    
    if ( !process )
    {
        process = new QProcess(this);
        processHash.insert(process,_from);
        connect(process, SIGNAL( readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
        connect(process, SIGNAL( finished(int)), this, SLOT(finishedProcess(int)));
//        qDebug("Create process.");
    }
    else
    {
    //    qDebug("Process already created.");
    }
    
     // Если сообщение проишло в html формате, то конвертируем его...
    QString msg;
    if( _html )
    {
        QTextDocument doc;
        doc.setHtml(_msg);
        msg = doc.toPlainText();
    }
    else
        msg = _msg;
        
    // Если программа не запущена, то запустими её.
    if( process->state() == QProcess::NotRunning )
    {
        QString command_temp = command;
        command_temp.replace(tr("$ip"),_from->get_ip().toString());
        command_temp.replace(tr("$name"),_from->get_name());
        command_temp.replace(tr("$host"),_from->get_host());
        command_temp.replace(tr("$msg"),msg);
        process->start(command_temp);
    //    qDebug() << tr("Programm started: %1").arg( process->state() == QProcess::NotRunning ? false:true);        
    }
    
    // Также пошлем сообщение с стандартный поток.
    QTextStream in(process);
    in << msg << endl;
    
    dLocalUserEx::event_msg_personal(_from,_msg,_html);
}

void dLocalCommandUserEx::readyReadStandardOutput()
{
    QProcess *process = qobject_cast<QProcess *>(sender());    
    if( processHash.contains( process ) )
    {
        dPUser usr = processHash.value(process);
        QByteArray result = process->readAll();
        usr->send_msg(QString::fromLocal8Bit(result),get_pointer());
        usr->send_auto_answer(get_pointer());
    }
}

void dLocalCommandUserEx::finishedProcess ( int _exitCode )
{
  //  readyReadStandardOutput();
 //   qDebug("Programm finished.");
}


