#include "dlogwindow.h"

#include "../netex/dmanagerex.h"

#include "../dchatapplication.h"
#include "../dsettinggeneral.h"
#include "../dsetting.h"
#include "../dview.h"

dLogWindow::dLogWindow( QWidget * _parent, Qt::WFlags _flags):
        QMainWindow(_parent,_flags)
{
    application = qobject_cast<dChatApplication*>(QApplication::instance());

    settingLogWindow = new dSetting(tr("log_window"),application->settingGeneral);
    settingLogWindow->setNode(false);

    QDomElement rootElement = logDocument.createElement("messages");
    logDocument.appendChild(rootElement);
    rootElement.setAttribute(tr("start"),QDateTime::currentDateTime().toString(Qt::TextDate));
     
    setWindowIcon( QIcon(tr("pic/gear64x64.png")) );
    setWindowTitle(tr("Логи/Системные сообщения."));
    
    resize ( 640,480 );
    setWindowState(Qt::WindowMaximized);
    
    contentsWidget = new QDockWidget(tr("Содержание"),_parent,Qt::Drawer);
    contentsWidget->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);
    contentsWidget->setObjectName(tr("contentswidget_log_win"));
    addDockWidget(Qt::LeftDockWidgetArea,contentsWidget);
    
    QListWidget *contentsList =  new QListWidget();
    contentsList->setIconSize(QSize(48,48));
    QListWidgetItem *item;
    item = new QListWidgetItem(tr("Системные сообщения"),contentsList);
    item->setIcon(QIcon(tr("pic/feather64x64.png")));
    item = new QListWidgetItem(tr("Массовые сообщения"),contentsList);
    item->setIcon(QIcon(tr("pic/closet64x64.png")));
    item = new QListWidgetItem(tr("Лог личных сообщений"),contentsList);
    item->setIcon(QIcon(tr("pic/closet64x64.png")));
    contentsWidget->setWidget(contentsList);
    connect(contentsList, SIGNAL(currentRowChanged (int)),
    this, SLOT( itemChanged (int)));

    QAction *clearAct = new QAction(tr("Очистить"), this);
    clearAct->setEnabled(true);
    clearAct->setIcon( QIcon(tr("pic/new32x32.png")) );
    clearAct->setShortcut(tr("Ctrl+N"));
    connect(clearAct, SIGNAL(triggered()), this, SLOT(clearLog()));
//    connect(openAct, SIGNAL(triggered()), this, SLOT(openSetting()));
/*
    QAction *saveAct = new QAction(tr("Сохранить"), this);
    saveAct->setEnabled(true);
    saveAct->setIcon( QIcon(tr("pic/save32x32.png")) );
    saveAct->setShortcut(tr("Ctrl+S"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(saveSetting()));
*/
    QAction *dockShowAct = new QAction(tr("Панель логов"), this);
    dockShowAct->setCheckable(true);
    dockShowAct->setChecked ( true );
    dockShowAct->setEnabled(true);
    dockShowAct->setIcon( QIcon(tr("pic/win24x24.png")) );
    dockShowAct->setShortcut(tr("Ctrl+L"));
    connect(dockShowAct, SIGNAL(toggled(bool)), this, SLOT(closeSideWindow(bool)));

    QToolBar *toolbar = new QToolBar ( tr("ToolsBar"), this);
    toolbar->setObjectName(tr("toolbar_log_win"));

    toolbar->addAction(clearAct);
    toolbar->addSeparator();
    toolbar->addAction(dockShowAct);   
    addToolBar(toolbar);
    
    systemMessageEditor = new QTextEdit();
    systemMessageEditor->setReadOnly(true);
    
    massMessageTable = new dView<QTableWidget>();
    QStringList labels;
    labels << tr("Время:") << tr("От кого:") << tr("IP:") << tr("Для кого:") << tr("IP:") << tr("Тип:") << tr("Сообщение:");
    massMessageTable->setEditTriggers(false);        
    massMessageTable->setSelectionBehavior( QAbstractItemView::SelectRows );
    massMessageTable->setColumnCount(7);
    massMessageTable->setHorizontalHeaderLabels(labels);
    massMessageTable->setSelectionMode(QAbstractItemView::SingleSelection);
    massMessageTable->horizontalHeader()->setStretchLastSection( true );
    massMessageTable->horizontalHeader()->setHighlightSections(false);
    massMessageTable->verticalHeader()->setHighlightSections(false);
    massMessageTable->verticalHeader()->hide();
    // Востановим размеры заголовка.
    settingLogWindow->getHeaderSize(tr("mass_table_header_sizes"),massMessageTable->horizontalHeader());
    //------
    connect(massMessageTable , SIGNAL(itemDoubleClicked (QTableWidgetItem*)), this, SLOT(tableDoubleClicked(QTableWidgetItem*)));

    QTextEdit *systemMessageEditor2 = new QTextEdit();
    QWidget *tempWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(1);
    layout->setSpacing(5);
    doubleCheckBox = new QCheckBox("Убрать повторяющиеся");
    // Востановим состояние QCheckBox.
    if( !settingLogWindow->toInt(tr("double_mass"),tr("value"),2) )
        doubleCheckBox->setCheckState(Qt::Unchecked);
    else
        doubleCheckBox->setCheckState(Qt::Checked);
    
    connect(doubleCheckBox, SIGNAL(stateChanged(int)), this, SLOT(doubleMassStateChanged(int)));
    layout->addWidget( doubleCheckBox );
    layout->addWidget( massMessageTable );   
    
    tempWidget->setLayout(layout); 
    
    centralWidget =  new QStackedWidget(); 
    centralWidget->addWidget(systemMessageEditor);
    centralWidget->addWidget(tempWidget);

    messageLogTable = new QTableWidget();
    labels.clear();
    labels << tr("Дата/Время:") << tr("От кого:") << tr("IP:") << tr("Для кого:") << tr("IP:") << tr("Тип:") << tr("Сообщение:");
    messageLogTable->setEditTriggers(false);        
    messageLogTable->setSelectionBehavior( QAbstractItemView::SelectRows );
    messageLogTable->setColumnCount(7);
    messageLogTable->setHorizontalHeaderLabels(labels);
    messageLogTable->setSelectionMode(QAbstractItemView::SingleSelection);
    messageLogTable->horizontalHeader()->setStretchLastSection( true );
    messageLogTable->horizontalHeader()->setHighlightSections(false);
    messageLogTable->verticalHeader()->setHighlightSections(false);
    messageLogTable->verticalHeader()->hide();
    // Востановим размеры заголовка таблицы.
    settingLogWindow->getHeaderSize(tr("log_table_header_sizes"),messageLogTable->horizontalHeader());
    //------
    connect(messageLogTable , SIGNAL(itemDoubleClicked (QTableWidgetItem*)), this, SLOT(tableDoubleClicked(QTableWidgetItem*)));

    // Загрузим старые логи сообщений.
    QStringList masks;
    QString log_dir = settingLogWindow->get(tr("log_dir"),tr("value"),tr("logs/"));
    masks << tr("messages*.xml");
    QDir dir(log_dir);
    QStringList files = dir.entryList(masks,QDir::Files,QDir::Time|QDir::Reversed);
    foreach( QString filename, files )
    {
        QFile file(log_dir+filename);
        QDomDocument oldlogDocument;
        if ( file.open(QFile::ReadOnly | QFile::Text) && oldlogDocument.setContent(&file)) 
        {
            QDomElement rootElement = oldlogDocument.documentElement();
            QDomElement messageElement = rootElement.firstChildElement();
            while (!messageElement.isNull()) {
                if ( messageElement.tagName() == tr("message") )
                {
                    QString date_time = messageElement.attribute(tr("date_time"));
                    QDomElement fromElement =messageElement.firstChildElement(tr("from"));
                    QString fromName = fromElement.attribute(tr("name"));
                    QString fromIp = fromElement.attribute(tr("ip"));
                    QDomElement toElement =messageElement.firstChildElement(tr("to"));
                    QString toName = toElement.attribute(tr("name"));
                    QString toIp = toElement.attribute(tr("ip"));
                    QDomElement msgElement = messageElement.firstChildElement(tr("data"));
                    QString msg = msgElement.text();
                    bool html = ( msgElement.attribute(tr("data_type")) == tr("html"));
                    addLogTable( date_time, fromName, fromIp, toName, toIp, msg,html);
                }
                messageElement = messageElement.nextSiblingElement();
            }
        }
    }
    centralWidget->addWidget(messageLogTable);
// Позиционируем курсор... в содержании....
    int cur_item = settingLogWindow->toInt(tr("content_current_item"),tr("item"),0);
    contentsList->setCurrentRow(cur_item);
    centralWidget->setCurrentIndex(cur_item);
//--------
    setCentralWidget (centralWidget);

    // Востановим состояние окна.
    QByteArray state = settingLogWindow->toByteArray(tr("window_state"),saveState());
    restoreState(state);
};

dLogWindow::~dLogWindow()
{
    QString log_dir = settingLogWindow->get(tr("log_dir"),tr("value"),tr("logs/"));

    QDomElement rootElement = logDocument.documentElement();
    rootElement.setAttribute(tr("end"),QDateTime::currentDateTime().toString(Qt::TextDate));
    QString filename = log_dir+tr("messages%1.xml").arg(QDateTime::currentDateTime().toString(tr("dd-MM-yyyy(hh-mm-ss)")));
    QFile file(filename);
    if (file.open(QFile::WriteOnly | QFile::Text)) 
    {
        QTextStream out(&file);
        logDocument.save(out, 5);
    }
    // Сохраним текущий пункт меню...
    settingLogWindow->set(tr("content_current_item"),tr("item"),centralWidget->currentIndex());
    // Сохраним состояние окна.
    settingLogWindow->set(tr("window_state"),saveState());
    // Сохраним размеры заголовка таблиц.
    settingLogWindow->setHeaderSize(tr("mass_table_header_sizes"),massMessageTable->horizontalHeader());
    settingLogWindow->setHeaderSize(tr("log_table_header_sizes"),messageLogTable->horizontalHeader());
    // Удалим настройки.
    delete settingLogWindow;
    
};

void dLogWindow::itemChanged ( int _index )
{
    centralWidget->setCurrentIndex(_index);
}

QString dLogWindow::escapeXml(QString xml)
{
    xml.replace("&", "&amp;");
    xml.replace("<", "&lt;");
    xml.replace(">", "&gt;");
    xml.replace(" ", "&apos;");
    xml.replace("\"", "&quot;");
    return xml;
}

void dLogWindow::slot_msg_auto_answer( dPUser _from, dPUser _to, const QString & _msg )
{
    QTime time(QTime::currentTime());
    int messageSize = 200;
    systemMessageEditor->insertHtml(tr("<font color=\"#FC0600\">[%1] Сообщение для %2 дошло, поступил авто-ответ:<br></font>").arg(time.toString()).arg(_from->get_name()));
    if( _msg.size() < messageSize )
        systemMessageEditor->insertHtml(tr("<font color=\"#FC0600\"><i>%1</i><br></font>").arg(_msg));
    else
        systemMessageEditor->insertHtml(tr("<font color=\"#FC0600\"><i>... %1</i><br></font>").arg(_msg.right(messageSize)));
};

void dLogWindow::slot_msg_channel( dPUser _from, const QString & _msg )
{
    QTime time(QTime::currentTime());
    systemMessageEditor->insertHtml(tr("<font color=\"#FD5900\">[%1] Сообщение в канал от %2:<br></font>").arg(time.toString()).arg(_from->get_name()));
    if( _msg.size() < 50 )
        systemMessageEditor->insertHtml(tr("<font color=\"#FD5900\"><i>%1</i><br></font>").arg(_msg));
    else
        systemMessageEditor->insertHtml(tr("<font color=\"#FD5900\"><i>... %1</i><br></font>").arg(_msg.right(50)));
};

void dLogWindow::slot_change_topic( const QString & _topic )
{
};
void dLogWindow::slot_msg_channel_me( dPUser _from, const QString & _msg )
{
    QTime time(QTime::currentTime());
    systemMessageEditor->insertHtml(tr("<font color=\"#FD5900\">[%1] Пельзователь %2 шепнул:<br></font>").arg(time.toString()).arg(_from->get_name()));
    if( _msg.size() < 50 )
        systemMessageEditor->insertHtml(tr("<font color=\"#FD5900\"><i>%1</i><br></font>").arg(_msg));
    else
        systemMessageEditor->insertHtml(tr("<font color=\"#FD5900\"><i>... %1</i><br></font>").arg(_msg.right(50)));
};
void dLogWindow::slot_msg_enter( dPUser _from )
{
    QTime time(QTime::currentTime());
    systemMessageEditor->insertHtml(tr("<font color=\"#900300\">[%1] Пользователь %2 вошел в сеть.<br></font>").arg(time.toString()).arg(_from->get_name()));
};
void dLogWindow::slot_msg_exit( dPUser _from )
{
    QTime time(QTime::currentTime());
    systemMessageEditor->insertHtml(tr("<font color=\"#900300\">[%1] Пользователь %2 вышел из сети.<br></font>").arg(time.toString()).arg(_from->get_name()));
};
void dLogWindow::slot_msg_beep( dPUser _from, dPUser _to)
{
    QTime time(QTime::currentTime());
    systemMessageEditor->insertHtml(tr("<font color=\"#F18200\">[%1] Поступил звуковой сигнал от %2 для %3<br></font>").arg(time.toString()).arg(_from->get_name()).arg(_to->get_name()));
};
void dLogWindow::slot_msg_personal( dPUser _from, dPUser _to, const QString & _msg ,bool _html)
{
    QTime time(QTime::currentTime());
    systemMessageEditor->insertHtml(tr("<font color=\"#FC0600\">[%1] Поступило личное сообщение от %2 для %3:<br></font>").arg(time.toString()).arg(_from->get_name()).arg(_to->get_name()));
    if( _msg.size() < 50 )
        systemMessageEditor->insertHtml(tr("<font color=\"#FC0600\"><i>%1</i><br></font>").arg(_msg));
    else
        systemMessageEditor->insertHtml(tr("<font color=\"#FC0600\"><i>... %1</i><br></font>").arg(_msg.right(50)));

    bool html = _html;
    addLogTable(QDateTime::currentDateTime().toString(),
                _from->get_name(),
                _from->get_ip().toString(),
                _to->get_name(),
                _to->get_ip().toString(),
                _msg,
                html );
        
    QDomElement rootElement = logDocument.documentElement();
    QDomElement messageElement = logDocument.createElement("message");
    rootElement.appendChild(messageElement);
    messageElement.setAttribute(tr("date_time"),QDateTime::currentDateTime().toString(Qt::TextDate));

    QDomElement fromElement = logDocument.createElement("from");
    messageElement.appendChild(fromElement);
    fromElement.setAttribute(tr("name"),_from->get_name());
    fromElement.setAttribute(tr("ip"),_from->get_ip().toString());
    
    QDomElement toElement = logDocument.createElement("to");
    messageElement.appendChild(toElement);
    toElement.setAttribute(tr("name"),_to->get_name());
    toElement.setAttribute(tr("ip"),_to->get_ip().toString());

    QDomElement textElement = logDocument.createElement("data");
    messageElement.appendChild(textElement);
    
    if( html )
        textElement.setAttribute(tr("data_type"),tr("html"));        
    else
        textElement.setAttribute(tr("data_type"),tr("text"));

    QDomText text = logDocument.createTextNode(_msg);
    textElement.appendChild(text);

};
void dLogWindow::slot_msg_mass( dPUser _from, dPUser _to, const QString & _msg, bool _html )
{
    QTime time(QTime::currentTime());
    systemMessageEditor->insertHtml(tr("<font color=\"#1E00FF\">[%1] Поступило массовое сообщение от %2 для %3:<br></font>").arg(time.toString()).arg(_from->get_name()).arg(_to->get_name()));
    if( _msg.size() < 50 )
        systemMessageEditor->insertHtml(tr("<font color=\"#1E00FF\"><i>%1</i><br></font>").arg(_msg));
    else
        systemMessageEditor->insertHtml(tr("<font color=\"#1E00FF\"><i>... %1</i><br></font>").arg(_msg.right(50)));
    
    int rowCount = massMessageTable->rowCount();
    massMessageTable->setRowCount(rowCount+1);
    QTableWidgetItem *item; 
    item = new QTableWidgetItem(time.toString());
    massMessageTable->setItem(rowCount,0,item);

    item = new QTableWidgetItem(_from->get_name());
    item->setIcon(QIcon(_from->get_avatar()));
    massMessageTable->setItem(rowCount,1,item);

    item = new QTableWidgetItem(_from->get_ip().toString());
    massMessageTable->setItem(rowCount,2,item);

    item = new QTableWidgetItem(_to->get_name());
    item->setIcon(QIcon(_to->get_avatar()));
    massMessageTable->setItem(rowCount,3,item);

    item = new QTableWidgetItem(_to->get_ip().toString());
    massMessageTable->setItem(rowCount,4,item);

    bool html = _html;
    item = new QTableWidgetItem( html?tr("html"):tr("text") );
    massMessageTable->setItem(rowCount,5,item);
    if( html )
    {
        QTextDocument doc;
        doc.setHtml(_msg);
        item = new QTableWidgetItem(doc.toPlainText());
    }
    else
        item = new QTableWidgetItem(_msg);
    item->setTextAlignment(Qt::AlignLeft|Qt::AlignTop);
    item->setData(Qt::UserRole,QVariant(_msg));
    massMessageTable->setItem(rowCount,6,item);
    
    // Уберем повторяющиеся сообщения из таблицы если поствлена галочка.
    if( doubleCheckBox->checkState() && rowCount != 0 )
    {
        QTableWidgetItem * item_prev = massMessageTable->item(rowCount-1,6);
        if( item_prev->text() == item->text() )
            massMessageTable->hideRow( rowCount );
    }

};
void dLogWindow::slot_msg_rename( dPUser _from, const QString & _oldname )
{
    QTime time(QTime::currentTime());
    systemMessageEditor->insertHtml(tr("<font color=\"#0096E6\">[%1] Пользователь переименовался из %2 в %3<br></font>").arg(time.toString()).arg(_oldname).arg(_from->get_name()));
};

void dLogWindow::closeSideWindow( bool _checked )
{
    if( _checked )
        contentsWidget->show();
    else
        contentsWidget->hide();
};

void dLogWindow::clearLog()
{
    if( centralWidget->currentIndex() == 0 )
        systemMessageEditor->clear();
    if( centralWidget->currentIndex() == 1 )
    {
        int rowCount = massMessageTable->rowCount();
        for( int i = 0; i < rowCount; i++)
            massMessageTable->removeRow(0);

/*
        massMessageTable->clear();
        QStringList labels;
        labels << tr("Время:") << tr("От кого:") << tr("Для кого:") << tr("Сообщение:");
        massMessageTable->setHorizontalHeaderLabels(labels);
*/
    }
};

void dLogWindow::tableDoubleClicked ( QTableWidgetItem * _item )
{
    QTableWidget * table = _item->tableWidget();
     
    QString ip = table->item(table->currentRow(),2)->text();
    QString name = table->item(table->currentRow(),1)->text();
    dPUser from = application->get_managerEx()->find_user( QHostAddress(ip), name );

    if( !from )
    {
        if (QMessageBox::information(0, QObject::tr("Пользователь не найден в списке."),
                          tr("Пользователь %1 (IP:%2) либо уже вышел из сети, либо не занесен\n в список, вы хотите открыть сообщение?").arg(name).arg(ip),QMessageBox::Yes,QMessageBox::No,0) == QMessageBox::No )
            return;
        else
            from = application->get_managerEx()->get_main_user();
    }
    QString msg = table->item(table->currentRow(),6)->data(Qt::UserRole).toString();    
    bool html = ( table->item(table->currentRow(),5)->text() == tr("html"));

    application->createMessageEditor(   from,
                                        from->get_main_user(),
                                        msg,
                                        tr("Ответ на сообщение от %1 (%2)").arg(from->get_name()).arg(from->get_ip().toString()),
                                        dChatApplication::msg_personal,
                                        true,
                                        html);    
}

void dLogWindow::doubleMassStateChanged ( int _state )
{
    if( _state == 0 )
        for( int i=0; i<massMessageTable->rowCount(); i++ )
            massMessageTable->showRow( i );
    if( _state == 2 )
        for( int i=1; i<massMessageTable->rowCount(); i++ )
        {
            QTableWidgetItem * item = massMessageTable->item(i,6);
            QTableWidgetItem * item_prev = massMessageTable->item(i-1,6);
            if( item_prev->text() == item->text() )
                massMessageTable->hideRow( i );
        }   
    settingLogWindow->set(tr("double_mass"),tr("value"),_state);
}
void dLogWindow::addLogTable(   const QString & _date_time,
                                const QString & _fromName,
                                const QString & _fromIp,
                                const QString & _toName,
                                const QString & _toIp,
                                const QString & _msg,
                                bool _html )
{
    QTableWidgetItem *item; 
    messageLogTable->insertRow(0);
    item = new QTableWidgetItem(_date_time);
    messageLogTable->setItem(0,0,item);
    item = new QTableWidgetItem(_fromName);
    messageLogTable->setItem(0,1,item);
    item = new QTableWidgetItem(_fromIp);
    messageLogTable->setItem(0,2,item);
    item = new QTableWidgetItem(_toName);
    messageLogTable->setItem(0,3,item);
    item = new QTableWidgetItem(_toIp);
    messageLogTable->setItem(0,4,item);
    item = new QTableWidgetItem( _html?tr("html"):tr("text") );
    messageLogTable->setItem(0,5,item);
    if( _html )
    {
        QTextDocument doc;
        doc.setHtml(_msg);
        item = new QTableWidgetItem(doc.toPlainText());
    }
    else
        item = new QTableWidgetItem(_msg);
    item->setTextAlignment(Qt::AlignLeft|Qt::AlignTop);
    item->setData(Qt::UserRole,QVariant(_msg));
    messageLogTable->setItem(0,6,item);
    
  // Почему-то не работает!!!
  //  messageLogTable->resizeRowToContents(0);
    
}



