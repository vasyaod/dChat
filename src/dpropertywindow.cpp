#include "dpropertywindow.h"

dPropertyWindow::dPropertyWindow(dSetting *_setting ,QWidget * _parent, Qt::WFlags _flags):
        QMainWindow(_parent,_flags),
        setting(_setting)
{
    curentSelectedSetting = _setting;
    setWindowIcon( QIcon(tr("pic/gear64x64.png")) );
    setWindowTitle(tr("Настройки."));
    
    resize ( 640,480 );
    setWindowState(Qt::WindowMaximized);
    
    contentsWidget = new QDockWidget(tr("Дерево параметров"),_parent,Qt::Drawer);
    contentsWidget->setObjectName(tr("contentswidget_property_win"));

 //   contentsWidget->resize(220,100);
    contentsWidget->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);
    
    addDockWidget(Qt::LeftDockWidgetArea,contentsWidget);
    
    contentsTree =  new QTreeWidget();
    contentsTree->setColumnCount ( 1 ); 
    contentsTree->header()->hide();
    contentsTree->setIconSize(QSize(48,48));
    contentsWidget->setWidget(contentsTree);
    
    
    QAction *openAct = new QAction(tr("Открыть"), this);
    openAct->setEnabled(true);
    openAct->setIcon( QIcon(tr("pic/open32x32.png")) );
    openAct->setShortcut(tr("Ctrl+O"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(openSetting()));

    QAction *saveAct = new QAction(tr("Сохранить"), this);
    saveAct->setEnabled(true);
    saveAct->setIcon( QIcon(tr("pic/save32x32.png")) );
    saveAct->setShortcut(tr("Ctrl+S"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(saveSetting()));

    QAction *dockShowAct = new QAction(tr("Дерево настроек"), this);
    dockShowAct->setCheckable(true);
    dockShowAct->setChecked ( true );
    dockShowAct->setEnabled(true);
    dockShowAct->setIcon( QIcon(tr("pic/win24x24.png")) );
    dockShowAct->setShortcut(tr("Ctrl+W"));
    connect(dockShowAct, SIGNAL(toggled(bool)), this, SLOT(closeSideWindow(bool)));

    QToolBar *toolbar = new QToolBar ( tr("ToolsBar"), this);
    toolbar->setObjectName(tr("toolbar_property_win"));
   // toolbar->setMaximumSize(0xFFFFF,20);
    toolbar->addAction(openAct);
    toolbar->addAction(saveAct);
    toolbar->addSeparator();
    toolbar->addAction(dockShowAct);   
    addToolBar(toolbar);

    connect(contentsTree,
            SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem* )),
            this,
            SLOT(itemChanged( QTreeWidgetItem*, QTreeWidgetItem* )));
        
    propertyList =  new QScrollArea();
    propertyList_second = new QWidget();
    propertyList->setWidget (propertyList_second);     
    setCentralWidget (propertyList);
    
    parseSetting(_setting);

    //contentsTree->setItemSelected( contentsTree->takeTopLevelItem ( 0 ), true );
    // Тут какой-то глюк был пришлось мудрить!
    QTreeWidgetItem * current = new QTreeWidgetItem();
    current->setData(0,Qt::UserRole,(int)_setting);
    this->itemChanged( current , current  );
    delete current;

    connect(setting, SIGNAL(reParsingSignal()),
            this,SLOT(reParsing()));

    // Востановим состояние окна.
    QByteArray state = setting->toByteArray(tr("property_window_state"),saveState());
    restoreState(state);
};

dPropertyWindow::~dPropertyWindow()
{
    setting->set(tr("property_window_state"),saveState());    
}

void dPropertyWindow::parseSetting(dSetting *_setting, QTreeWidgetItem *parentItem )
{
    QTreeWidgetItem *item;
    dSetting *temp;
   
    if (parentItem) {
        item = new QTreeWidgetItem(parentItem);
    } else {
        contentsTree->clear();
        item = new QTreeWidgetItem(contentsTree);
        
    }
    item->setText(0, _setting->getTitle());
    item->setData(0,Qt::UserRole,(int)_setting);
    item->setIcon(0, !_setting->getIcon().isNull() ? _setting->getIcon():QIcon(tr("pic/gear64x64.png")) );
    
    itemForSetting.insert(_setting,item);
    
    QList<dSetting*> children = _setting->children();
    QListIterator<dSetting*> i(children);
    while (i.hasNext())
    {   
        temp = i.next();
        if ( temp->isNode() ) 
            parseSetting( temp,item );  
        else
            itemForSetting.insert(temp,item);
    }
    // Какойто глюк в библиотеке, я не виноват!!!
  //  if( curentSelectedSetting == _setting)
  //       contentsTree->setCurrentItem(item);

    contentsTree->setItemExpanded(item,true);
    contentsTree->update();
};

void dPropertyWindow::itemChanged( QTreeWidgetItem * current, QTreeWidgetItem * previous  )
{
    dSetting *temp;
    QGroupBox *groupBox;
    QHBoxLayout *layoutGroupBox;
    QWidget *tempWidget;
    
    if( current )
    {
        dSetting * seting = (dSetting*)current->data( 0, Qt::UserRole).toInt();
        if ( !seting )
            return;
        
        // Изменим текущий выделеный сетинг.
        curentSelectedSetting = seting;
        
        QVBoxLayout *layout = new QVBoxLayout;
        layout->setMargin(1);
        layout->setSpacing(2);
        
        tempWidget = seting->createWidget();
        // Проверим есть-ли в узле виджет... его там жожет и не быть!
        if( tempWidget )
        {
            groupBox = new QGroupBox(seting->getTitle());
            layoutGroupBox= new QHBoxLayout;
            layoutGroupBox->setMargin(3);
            layoutGroupBox->addWidget( tempWidget );   
            groupBox->setLayout(layoutGroupBox);
            layout->addWidget( groupBox );   
        }
        
        QList<dSetting*> children = seting->children();
        QListIterator<dSetting*> i(children);
        while (i.hasNext())
        {
            temp = i.next();
            if ( !temp->isNode() && ( tempWidget = temp->createWidget() )) 
            {
                groupBox = new QGroupBox(temp->getTitle());
                layoutGroupBox= new QHBoxLayout;
                layoutGroupBox->setMargin(3);
                layoutGroupBox->addWidget( tempWidget );   
                groupBox->setLayout(layoutGroupBox);
                
                layout->addWidget( groupBox );
            }
        }
        layout->addStretch ( 1 );
        //layout->addItem( new QSpacerItem(2000,2000, QSizePolicy::Expanding, QSizePolicy::Minimum) );
      
        delete propertyList_second;
        propertyList_second = new QWidget();
        propertyList_second->setLayout(layout); 
        propertyList->setWidgetResizable(true);
        propertyList->setWidget (propertyList_second);   
        propertyList_second->show();
      //  propertyList_second->update();
       // propertyList->update();
    }
}

void dPropertyWindow::openSetting()
{
    QString fileName =
            QFileDialog::getOpenFileName(this, tr("Открыть файл настроек программы"),
                                         QDir::currentPath(),
                                         tr("XML Files (*.xml)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Ошибка"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

};

void dPropertyWindow::saveSetting()
{
    QString fileName =
            QFileDialog::getSaveFileName(this, tr("Сохранить файл настроек как .."),
                                         QDir::currentPath(),
                                         tr("XML Files (*.xml)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Ошибка"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }
    
    QTextStream out(&file);
    setting->getXmlElement().ownerDocument().save(out, 5); 
}
void dPropertyWindow::closeSideWindow( bool _checked )
{
    if( _checked )
        contentsWidget->show();
    else
        contentsWidget->hide();
};

void dPropertyWindow::hideEvent ( QHideEvent * event )
{
    setting->saveSetting();
    QMainWindow::hideEvent(event);
}

void dPropertyWindow::reParsing()
{
    itemForSetting.clear();
    parseSetting(setting);
   // qDebug() << "++++++";
}

void dPropertyWindow::goSetting( dSetting *_setting )
{
    show(); 
    raise(); 
    if( itemForSetting.contains(_setting) )
    {
            contentsTree->setCurrentItem(itemForSetting.value(_setting));
    }
}

