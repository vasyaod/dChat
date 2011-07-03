#include "duserwindow.h"
#include "dchatapplication.h"
#include "dsettingwindow.h"
#include "dsettinguserwin.h"
#include "dview.h"

#include "netex/dmanagerex.h"
#include "dwindowframe/dwindowframe.h"
#include "dchannelwindow/dchannelwindow.h"
#include "dtopicwindow/dtopicwindow.h"
#include "dfriendswindow/dfriendswindow.h"
#include "dlistviewex/dlistviewex.h"

/*СПЕЦИАЛЬНО СОЗДАЮ КЛАСС ЧТОБЫ ПЕРЕХВАТИТЬ НАЖАТИЕ КЛАВИШЫ.
Жопа одним словом.....*/
class dMainWindowEx: public QMainWindow
{
    protected:
        virtual void keyPressEvent ( QKeyEvent * e );
        dUserWindow *userWindow;
    public:
        dMainWindowEx( dUserWindow *_userWindow, QWidget *_parent = 0):
                    QMainWindow(_parent),
                    userWindow(_userWindow){};        
};

void dMainWindowEx::keyPressEvent ( QKeyEvent * event )
{
    //&& event->modifiers() != Qt::META &&
//        event->modifiers() != Qt::CTRL && event->modifiers() != Qt::ALT )
    if(!(event->key() == Qt::Key_Backspace && userWindow->searchLineEdit->text().isEmpty()))
        if( !userWindow->searchLineEdit->hasFocus() &&
            ((event->text() >= tr("a") && event->text() <= tr("z")) ||
             (event->text() >= tr("A") && event->text() <= tr("Z")) ||
             (event->text() >= tr("0") && event->text() <= tr("9")) ||
             (event->text() >= tr("А") && event->text() <= tr("Я")) ||
             (event->text() >= tr("а") && event->text() <= tr("я")) ||
              event->key() == Qt::Key_Backspace) )
        {
            if( event->key() == Qt::Key_Backspace )
                userWindow->searchLineEdit->backspace();
            else
                userWindow->searchLineEdit->insert(event->text());
            userWindow->searchLineEdit->setFocus();
            // Откроем тус бар со строкой поиска(он может быть закрыт).
            userWindow->searchBar->setVisible(true);
        }

    QMainWindow::keyPressEvent(event);
        
}

dUserWindow::dUserWindow( dWindowFrame *_window ):
        window(_window)
{
    application = qobject_cast<dChatApplication*>(QApplication::instance());
    setParent(application);

    window->overloadMoveEvent();
    window->setMinimumSize(200,300);    // Минимальный размер...
    window->setMaxButton(false);        // Уберем кнопочку "развернуть во весь экран.".    
    window->setLeading(true);           // Сделаем ведущим...
    
    // Создадим лист пользователей....    
    settingWindow = new dSettingWindow(tr("user_window"),application->settingWindow,window);
    settingWindow->setTitle(tr("Настройки стиля главного окна"));

    settingUserWindow = new dSettingUserWin(tr("user_windows_other"),application->settingWindow,this);
    settingUserWindow->setIcon(QIcon(tr("pic/list64x64.png")));
    settingUserWindow->setTitle(tr("Настройки главного окна"));

    listWidget =  new dMainWindowEx(this,window);
    // Строка поиска пользователей...

//  Вставляем тулс бар....
    toolbar = new QToolBar ( tr("Основная панель"));
    toolbar->setObjectName(tr("toolbar"));
// Создаем бар со строкой для поиска
    searchBar = new QToolBar ( tr("Панель поиска"));
    searchBar->setObjectName(tr("searchbar"));
    searchLineEdit = new QLineEdit();
    connect(searchLineEdit, SIGNAL(textChanged( const QString&)), this, SLOT(searchTextChanged( const QString&)));
    searchBar->addWidget(searchLineEdit);
    
// Создаем бар с числом пользователей
    numberUserBar = new QToolBar ( tr("Число пользователей"));
    numberUserBar->setObjectName(tr("numberuserbar"));
    numberUserLabel = new QLabel(tr("Число пользователей: -"));
    numberUserLabel->setMinimumHeight(16);
    numberUserBar->addWidget(numberUserLabel);
    
    makeAction();
    //  Вставляем меню.......
    menuBar = new QMenuBar();
    QMenu *viewMenu = new QMenu(tr("Вид"));
        QMenu *panelsMenu = new QMenu(tr("Панели"));
        panelsMenu->addAction(toolbar->toggleViewAction());
        panelsMenu->addAction(searchBar->toggleViewAction());
        panelsMenu->addAction(numberUserBar->toggleViewAction());        
    viewMenu->addMenu(panelsMenu);
    viewMenu->addSeparator();
    viewMenu->addAction(viewBarAct);
    viewMenu->addAction(viewIconAct);
    viewMenu->addAction(viewListAct);
    viewMenu->addAction(viewTableAct);
    menuBar->addMenu(viewMenu);

    windowMenu = application->getWindowMenu();
    windowMenu->addSeparator();
    windowMenu->addAction(allParametersAct);
    windowMenu->addAction(logWindowAct);
    menuBar->addMenu(windowMenu);

    usersMenu = new QMenu(tr("Юзеры"));
    usersActionGroup = new QActionGroup(this);
    menuBar->addMenu(usersMenu);

    QMenu *actionsMenu = new QMenu(tr("Действия"));
    actionsMenu->addAction(refreshAct);    
    actionsMenu->addSeparator();
    actionsMenu->addAction(sendMessageAct);    
    actionsMenu->addAction(sendBeepAct);    
    actionsMenu->addAction(userInfoAct);    
    actionsMenu->addAction(userInfoRefreshAct);    
    actionsMenu->addSeparator();
    actionsMenu->addAction(sendMassAct);    
    actionsMenu->addAction(sendPersonalMassAct);

    menuBar->addMenu(actionsMenu);
    
    pluginsMenu = new QMenu(tr("Плагины"));
    menuBar->addMenu(pluginsMenu);
// Вставляем актионы для тулс бара... 
    windowToolBar = new QToolBar ( tr("Панель окон"));
    windowToolBar->setObjectName(tr("toolbar_window"));
    panelsMenu->addAction(windowToolBar->toggleViewAction());
    windowToolBar->addAction(allParametersAct);
    windowToolBar->addAction(logWindowAct);
    foreach( dWindow*_window, application->getWindowList() )
        windowToolBar->addAction(_window->getWindowAct());

    QAction *typeViewAct = new QAction(tr("Вид"), this);    
    typeViewAct->setIcon(QIcon(tr("pic/type.png")));
    QMenu *viewMenu2 = new QMenu();
    viewMenu2->addAction(viewBarAct);
    viewMenu2->addAction(viewIconAct);
    viewMenu2->addAction(viewListAct);
    viewMenu2->addAction(viewTableAct);
    typeViewAct->setMenu(viewMenu2);
    toolbar->addAction(typeViewAct);
    toolbar->addAction(refreshAct);

//    QAction *windowsAct = new QAction(tr("Окна"), this);
//  windowsAct->setMenu(application->getWindowMenu());
//    toolbar->addAction(windowsAct);

    
    listWidget->setMenuBar(menuBar);
    listWidget->addToolBar(windowToolBar);
    listWidget->addToolBarBreak();
    listWidget->addToolBar(toolbar);
    listWidget->addToolBarBreak();
    listWidget->addToolBar(numberUserBar);
    listWidget->addToolBar(searchBar);
    //listWidget->addToolBarBreak();
    window->setCentralWidget(listWidget);
    
    // Востановим состояние окна.
    QByteArray state = settingUserWindow->toByteArray(tr("window_state"),listWidget->saveState());
    listWidget->restoreState(state);
    
    connect(window, SIGNAL(closed()), this, SLOT(closed()));
    connect(window, SIGNAL(minimized()), this, SLOT(minimized()));
    
//    window->show();
}

dUserWindow::~dUserWindow()
{    
    settingUserWindow->set(tr("window_state"),listWidget->saveState());
    delete settingUserWindow;
    delete settingWindow;
}

void dUserWindow::makeAction()
{
    allParametersAct = new QAction(tr("Параметры/Настройки"), this);
    allParametersAct->setShortcut(tr("Ctrl+P"));
    allParametersAct->setIcon(QIcon(tr("pic/gear64x64.png")));
    connect(allParametersAct, SIGNAL(triggered()), application, SLOT(showPropertyWindow()));

    logWindowAct = new QAction(tr("Логи/Системные сообщения"), this);
    logWindowAct->setShortcut(tr("Ctrl+L"));
    logWindowAct->setIcon(QIcon(tr("pic/closet64x64.png")));
    connect(logWindowAct, SIGNAL(triggered()), application, SLOT(showLogWindow()));
    
    refreshAct = new QAction(tr("Обновить список"), this);
    refreshAct->setIcon(QIcon(tr("pic/refresh24x24.png")));
    refreshAct->setEnabled(true);
    refreshAct->setShortcut(QKeySequence(Qt::Key_F5));
    connect(refreshAct, SIGNAL(triggered(bool)), this, SLOT(refreshTriggered(bool)));

    sendMassAct = new QAction(tr("Послать массовку"), this);
    sendMassAct->setIcon(QIcon(tr("pic/mail24x24.png")));
    connect(sendMassAct, SIGNAL(triggered(bool)), this, SLOT(sendMassTriggered(bool)));

    sendPersonalMassAct = new QAction(tr("Послать личную массовку"), this);
    sendPersonalMassAct->setIcon(QIcon(tr("pic/mail24x24.png")));
    connect(sendPersonalMassAct, SIGNAL(triggered(bool)), this, SLOT(sendPersonalMassTriggered(bool)));
  /****************************************************************/  
    sendMessageAct = new QAction(tr("Послать сообщение"), this);
    sendMessageAct->setEnabled(true);
    sendMessageAct->setIcon(QIcon(tr("pic/mail24x24.png")));
    sendMessageAct->setShortcut(QKeySequence(Qt::Key_Return));
    connect(sendMessageAct, SIGNAL(triggered(bool)), this, SLOT(sendMessageTriggered(bool)));
    contextListAct.push_back(sendMessageAct);
    
    sendBeepAct = new QAction(tr("Послать зв. вызов"), this);
    sendBeepAct->setEnabled(true);
    sendBeepAct->setIcon(QIcon(tr("pic/sound32x32.png")));
    connect(sendBeepAct, SIGNAL(triggered(bool)), this, SLOT(sendBeepTriggered(bool)));
    contextListAct.push_back(sendBeepAct);

    userInfoAct = new QAction(tr("Информация о пользователе"), this);
    userInfoAct->setEnabled(true);
    userInfoAct->setIcon(QIcon(tr("pic/question64x64.png")));
    connect(userInfoAct, SIGNAL(triggered(bool)), this, SLOT(userInfoTriggered(bool)));
    contextListAct.push_back(userInfoAct);
    
    userInfoRefreshAct = new QAction(tr("Обновить информацию"), this);
    userInfoRefreshAct->setEnabled(true);
    userInfoRefreshAct->setIcon(QIcon(tr("pic/refresh24x24.png")));
    contextListAct.push_back(userInfoRefreshAct);
    connect(userInfoRefreshAct, SIGNAL(triggered(bool)), this, SLOT(refreshInfoTriggered(bool)));

    QAction *separator1 = new QAction(this);
    separator1->setSeparator(true);
    contextListAct.push_back(separator1);

    application->contextUserMenu.addActions(contextListAct);
    
  /****************************************************************/  
    viewBarAct = new QAction(tr("Плитка"), this);
    viewBarAct->setCheckable(true);
    viewBarAct->setEnabled(true);
    connect(viewBarAct, SIGNAL(toggled(bool)), this, SLOT(viewBarToggled(bool)));

    viewIconAct = new QAction(tr("Значки"), this);
    viewIconAct->setCheckable(true);
    viewIconAct->setEnabled(true);
    connect(viewIconAct, SIGNAL(toggled(bool)), this, SLOT(viewIconToggled(bool)));
    
    viewListAct = new QAction(tr("Список"), this);
    viewListAct->setCheckable(true);
    viewListAct->setEnabled(true);
    connect(viewListAct, SIGNAL(toggled(bool)), this, SLOT(viewListToggled(bool)));

    viewTableAct = new QAction(tr("Таблица"), this);
    viewTableAct->setCheckable(true);
    viewTableAct->setEnabled(true);
    connect(viewTableAct, SIGNAL(toggled(bool)), this, SLOT(viewTableToggled(bool)));

    viewActGroup = new QActionGroup(this);
    viewActGroup->addAction(viewBarAct);
    viewActGroup->addAction(viewIconAct);
    viewActGroup->addAction(viewListAct);
    viewActGroup->addAction(viewTableAct);
    
	// Смотрим какой тип просмотра указан в файле настройки.
	switch( settingUserWindow->toInt(tr("view_type"),tr("value"),0) )
	{
		case 0:  viewBarAct->setChecked(true);
		break;
		case 1:  viewIconAct->setChecked(true);
		break;
		case 2:  viewListAct->setChecked(true);
		break;
		case 3:  viewTableAct->setChecked(true);
		break;
    }   
    

};

void dUserWindow::closed()
{
    int reply = QMessageBox::question(window, tr("Десять раз отмерь, один отрежь!"),
                                      tr("Вы действительно хотите покинуть сия замечательную,\n превосходную, посланную вам богом программу?"),
                                      QMessageBox::Yes,
                                      QMessageBox::No);
    if( reply == QMessageBox::Yes)
        application->quitChat();
};

void dUserWindow::minimized()
{
//    application->trayBarWindow->activateWindow();
#ifdef Q_WS_WIN
 //   application->trayBarWindow->hide();
#else
    application->trayBarWindow->setWindowState(Qt::WindowMinimized);
#endif   
    window->hide();
    foreach(dWindow *_window, application->getWindowList())
        _window->lower();
};

void dUserWindow::show()
{
    foreach(dWindow *_window, application->getWindowList())
        _window->start();
    window->show();
    window->raise();
    window->activateWindow();
    double b = settingWindow->toInt(tr("opacity"),tr("value"),100)+1;
    window->setWindowOpacity(b/100);
}

void dUserWindow::viewBarToggled ( bool checked )
{
    if( checked )
    {
        QString text = tr("Этот режим просмотра может некорректно работать.\nЭто связано с проблемами в библиотеке Qt.\nВы желаете его использовать?");
        if (QMessageBox::information(0, tr("Предупреждение."),
                                        text,QMessageBox::Yes,QMessageBox::No,0) == QMessageBox::No )
        {
            viewTableToggled(true);
            return;
        }
        searchBarListView  = createBarListView(true);
        userBarListView = createBarListView();
        searchBarListView->hide();
        
        splitter = new QSplitter(Qt::Vertical);
        splitter->addWidget(searchBarListView);
        splitter->addWidget(userBarListView);
        QList<int> sizes; 
        for( int i=0; i<splitter->count(); i++)
             sizes << settingUserWindow->toInt(tr("splitter_sizes"),tr("size%1").arg(i),int(splitter->width()/2));
        splitter->setSizes(sizes);
        connect(splitter, SIGNAL(splitterMoved( int,int)), this, SLOT(splitterMoved(int,int)));
                
        listWidget->setCentralWidget (splitter);  
        userBarListView->setModel(application->get_managerEx()->get_model());
        userBarListView->setSelectionModel(application->get_managerEx()->get_selectionModel());
        searchBarListView->setModel(application->get_managerEx()->get_model());
        searchBarListView->setSelectionModel(application->get_managerEx()->get_selectionModel());

        settingUserWindow->set(tr("view_type"),tr("value"),0);
        currentUserView = userBarListView;
        searchWidgetUpdate();
    }
    else
    {
        delete listWidget->centralWidget();
    }

}
void dUserWindow::viewIconToggled ( bool checked )
{
    if( checked )
    {
        userIconView = createIconView();
        searchIconView = createIconView(true);
        searchIconView->hide();

        splitter = new QSplitter(Qt::Vertical);
        splitter->addWidget(searchIconView);
        splitter->addWidget(userIconView);
        QList<int> sizes; 
        for( int i=0; i<splitter->count(); i++)
             sizes << settingUserWindow->toInt(tr("splitter_sizes"),tr("size%1").arg(i),int(splitter->width()/2));
        splitter->setSizes(sizes);
        connect(splitter, SIGNAL(splitterMoved( int,int)), this, SLOT(splitterMoved(int,int)));
                
        listWidget->setCentralWidget (splitter);
        settingUserWindow->set(tr("view_type"),tr("value"),1);
        currentUserView = userIconView;
        searchWidgetUpdate();
    }
    else
    {
        delete listWidget->centralWidget();
    }
}
void dUserWindow::viewListToggled ( bool checked )
{
    if( checked )
    {    
        userListView = createListView();
        searchListView = createListView(true);        
        searchListView->hide();
 
        splitter = new QSplitter(Qt::Vertical);
        splitter->addWidget(searchListView);
        splitter->addWidget(userListView);
        QList<int> sizes; 
        for( int i=0; i<splitter->count(); i++)
             sizes << settingUserWindow->toInt(tr("splitter_sizes"),tr("size%1").arg(i),int(splitter->width()/2));
        splitter->setSizes(sizes);
        connect(splitter, SIGNAL(splitterMoved( int,int)), this, SLOT(splitterMoved(int,int)));

        listWidget->setCentralWidget (splitter);
        settingUserWindow->set(tr("view_type"),tr("value"),2);
        currentUserView = userListView;
        searchWidgetUpdate();
    }
    else
    {
        delete listWidget->centralWidget();
    }    
}
void dUserWindow::viewTableToggled ( bool checked )
{
    if( checked )
    {

        userTableView = createTableView();
        searchTableView = createTableView(true);
        searchTableView->hide();
    // Востановим размеры заголовка.
        settingUserWindow->getHeaderSize(tr("table_header_sizes"),userTableView->horizontalHeader());
        settingUserWindow->getHeaderSize(tr("table_header_sizes_search"),searchTableView->horizontalHeader());
    //------
        connect(userTableView->horizontalHeader(), SIGNAL(sectionResized( int,int,int)), this, SLOT(tableHeaderResize(int,int,int)));
        splitter = new QSplitter(Qt::Vertical);
        splitter->addWidget(searchTableView);
        splitter->addWidget(userTableView);
        QList<int> sizes; 
        for( int i=0; i<splitter->count(); i++)
             sizes << settingUserWindow->toInt(tr("splitter_sizes"),tr("size%1").arg(i),int(splitter->width()/2));
        splitter->setSizes(sizes);
        connect(splitter, SIGNAL(splitterMoved( int,int)), this, SLOT(splitterMoved(int,int)));
            
        listWidget->setCentralWidget (splitter);    
        settingUserWindow->set(tr("view_type"),tr("value"),3);
        currentUserView = userTableView;
        searchWidgetUpdate();
    }
    else
    {
        delete listWidget->centralWidget();
    }
}

void dUserWindow::refreshTriggered ( bool checked  )
{
    dManagerEx *manager = application->get_managerEx();
    manager->send_mass_echo();
    manager->send_info_request(application->get_managerEx()->get_users(),manager->get_main_user());
    manager->send_image_request(application->get_managerEx()->get_users(),manager->get_main_user());
    
}

// Вызывается когда нужно послать звуковой вызов.
void dUserWindow::sendBeepTriggered ( bool checked  )
{
    dManagerEx *manager = application->get_managerEx();
    application->get_managerEx()->send_msg_beep(application->get_managerEx()->getSelectedUserToModel(),manager->get_main_user());
}

// Вызывается когда нужно послать сообщение.
void dUserWindow::sendMessageTriggered ( bool checked  )
{
    dManagerEx *manager = application->get_managerEx();
    application->createMessageEditor( manager->getSelectedUserToModel(),manager->get_main_user(),tr(""),tr("Новое сообщение."));
}
// Вызывается когда нужно послать массовое сообщение.
void dUserWindow::sendMassTriggered ( bool checked  )
{
    dManagerEx *manager = application->get_managerEx();
    application->createMessageEditor( manager->get_users(),manager->get_main_user(),tr(""),tr("Новое массовое сообщение."),dChatApplication::msg_mass);
}
// Вызывается когда нужно послать "личное" массовое сообщение.
void dUserWindow::sendPersonalMassTriggered ( bool checked  )
{
    dManagerEx *manager = application->get_managerEx();
    application->createMessageEditor( manager->get_users(),manager->get_main_user(),tr(""),tr("Новоя личная массовка."));
}

// Вызывается когда нужно показать информацию о пользователе.
void dUserWindow::userInfoTriggered ( bool checked  )
{
    dManagerEx *manager = application->get_managerEx();
    application->createUserInfoWindow( manager->getCurrentUserToModel() );
}

// Вызывается когда надо обновить информацию о пользователе. 
void dUserWindow::refreshInfoTriggered ( bool checked  )
{
    dPUser usr = application->get_managerEx()->getCurrentUserToModel();
    usr->send_info_request(usr->get_main_user());
    usr->send_image_request(usr->get_main_user());
}
void dUserWindow::itemDoubleClicked ( const QModelIndex & index )
{
    dManagerEx * manager = application->get_managerEx();
    application->createMessageEditor( manager->getSelectedUserToModel(),manager->get_main_user(),tr(""),tr("Новое сообщение."));    
}

void dUserWindow::customContextMenuRequested ( const QPoint & pos )
{
    /*
        qDebug() << connect( userListIconType, 
                SIGNAL(customContextMenuRequested (const QPoint&)),
                this,
                SLOT(customContextMenuRequested (const QPoint&))); 
     */
//    QMenu menu(listWidget->centralWidget());
//    menu.addAction(sendMessageAct);
//    menu.exec(window->pos()+pos);
  //  contextMenu->exec(pos);
};

dListViewEx *dUserWindow::createBarListView( bool searched )
{
    dListViewEx *list;
    if( searched )
        list = new dView<dListViewEx>(false);
    else
        list = new dListViewEx();
  
    // Добавим контекстное меню....
    application->contextUserMenu.addWidget(list);

 //   list->setSelectionMode(QAbstractItemView::ExtendedSelection);
 //   list->setContextMenuPolicy(Qt::ActionsContextMenu);
  //  list->setIconSize(QSize(48,48));
    list->setEditTriggers(false);
    
    connect(list, SIGNAL(doubleClicked ( const QModelIndex&)), this, SLOT(itemDoubleClicked( const QModelIndex&)));
    return list;
}
QListView *dUserWindow::createIconView( bool searched )
{
    QListView *list;
    if( searched )
        list = new dView<QListView>(false);
    else
        list = new QListView();
        
    // Добавим контекстное меню....
    application->contextUserMenu.addWidget(list);

    list->setContextMenuPolicy(Qt::ActionsContextMenu);
    list->setViewMode( QListView::IconMode );
    list->setModel(application->get_managerEx()->get_model());
    list->setSelectionMode(QAbstractItemView::ExtendedSelection);
    list->setSelectionModel(application->get_managerEx()->get_selectionModel());
    list->setEditTriggers(false);
    list->setIconSize(settingUserWindow->getIconSizeToIcon());

    connect(list, SIGNAL(doubleClicked ( const QModelIndex&)), this, SLOT(itemDoubleClicked( const QModelIndex&)));
    
    return list;
}
QListView *dUserWindow::createListView( bool searched )
{
    QListView *list;
    if( searched )
        list = new dView<QListView>(false);
    else
        list = new QListView();
        
    // Добавим контекстное меню....
    application->contextUserMenu.addWidget(list);

    list->setContextMenuPolicy(Qt::ActionsContextMenu);
    list->setViewMode( QListView::ListMode );
    list->setModel(application->get_managerEx()->get_model());
    list->setSelectionMode(QAbstractItemView::ExtendedSelection);
    list->setIconSize(settingUserWindow->getIconSizeToList());
    list->setSelectionModel(application->get_managerEx()->get_selectionModel());
    list->setEditTriggers(false);

    connect(list, SIGNAL(doubleClicked ( const QModelIndex&)), this, SLOT(itemDoubleClicked( const QModelIndex&)));

    return list;
}

QTableView *dUserWindow::createTableView( bool searched )
{
    QTableView *table;
    if( searched )
        table = new dView<QTableView>(false);
    else
        table = new QTableView();

    // Добавим контекстное меню....
    application->contextUserMenu.addWidget(table);
    
    table->setContextMenuPolicy(Qt::ActionsContextMenu);
    table->setModel(application->get_managerEx()->get_model());
    table->setSelectionModel(application->get_managerEx()->get_selectionModel());
    table->setSelectionMode(QAbstractItemView::ExtendedSelection );
    table->setSelectionBehavior( QAbstractItemView::SelectRows );
    table->setIconSize(settingUserWindow->getIconSizeToTable());
    table->verticalHeader()->hide();
    table->horizontalHeader()->setHighlightSections(false);
    table->setEditTriggers(false);
    table->hideColumn ( 7 );    
    table->hideColumn ( 6 );
    table->hideColumn ( 8 );

    connect(table, SIGNAL(doubleClicked ( const QModelIndex&)), this, SLOT(itemDoubleClicked( const QModelIndex&)));

    return table;
}
                
                    /*ПОИСК*/
void dUserWindow::searchTextChanged( const QString & _text )
{
    int flag = 0;
    int current = settingUserWindow->toInt(tr("view_type"),tr("value"),0);

    if( _text.isEmpty() )
    {
        flag = 0;
        if( !searchBar->isVisible() )
            searchBar->setVisible(false);
    }
    else
    {        
        QItemSelectionModel *selectionModel = application->get_managerEx()->get_selectionModel();
        QAbstractItemModel *model = application->get_managerEx()->get_model();

    // Это против глюка описаного чуть ниже.
        if ( current == 1 ) searchIconView->setRowHidden(model->rowCount()-1,false);

        QModelIndex index;
        for( int i = 0; i < model->rowCount(); i++ )
        {
            index = model->index(i,0);
            if( model->data(index).toString().contains(_text,Qt::CaseInsensitive) || 
                model->data(model->index(index.row(),1)).toString().contains(_text,Qt::CaseInsensitive) ||
                model->data(model->index(index.row(),2)).toString().contains(_text,Qt::CaseInsensitive))
            {
                switch( current )
                {
                    case 0:  searchBarListView->setRowHidden(i,false);
                    break;
                    case 1:  searchIconView->setRowHidden(i,false);
                    break;
                    case 2:  searchListView->setRowHidden(i,false);
                    break;
                    case 3:  searchTableView->setRowHidden(i,false);
                    break;
                }       
                flag = 1;
            }
            else
            {
                switch( current )
                {
                    case 0:  searchBarListView->setRowHidden(i,true);
                    break;
                    case 1: // Тут нельзя полностью скрыть все значки.
                            // Пришлось мудрить. ГЛЮК
                            if ( flag == 0 && i == model->rowCount()-1 )
                                searchIconView->hide();
                            else
                                searchIconView->setRowHidden(i,true);
                    break;
                    case 2:  searchListView->setRowHidden(i,true);
                    break;
                    case 3:  searchTableView->setRowHidden(i,true);
                    break;
                }                  
            }
        }
        
    }
    QWidget * widget;
    switch( current )
    {
        case 0:  widget = searchBarListView;
        break;
        case 1:  widget = searchIconView;
        break;
        case 2:  widget = searchListView;
        break;
        case 3:  widget = searchTableView;
        break;
    }  
    
    if( flag )
        widget->show();
    else
    {
        // Закроем окно с результатами поиск... так как этих результатов нет!
        widget->hide();
        currentUserView->setFocus();
    }
}

void dUserWindow::countUserChange( int _count )
{
    numberUserLabel->setText(tr("Число пользователей: %1 ").arg(_count));
}

//////////////////////////////////////////////////////////////
// Слот, реакция на перемещение сплитера.
void dUserWindow::splitterMoved( int,int )
{
    // Сохраним новые размеры спрлитера.
    QList<int> sizes = splitter->sizes(); 
    for( int i=0; i<sizes.size(); i++)
    {
        settingUserWindow->set(tr("splitter_sizes"),tr("size%1").arg(i),tr("%1").arg(sizes[i]));
    }
    
}

//////////////////////////////////////////////////////////////
// Слот, реакция на изменение размеров колонок в таблице,
// и последующее их сохранение(размеров).
void dUserWindow::tableHeaderResize( int logicalIndex, int oldSize, int newSize )
{
//        searchTableView = createTableView();
//        searchTableView->hide();
//        userTableView = createTableView();
    settingUserWindow->setHeaderSize(tr("table_header_sizes"),userTableView->horizontalHeader());
    settingUserWindow->setHeaderSize(tr("table_header_sizes_search"),searchTableView->horizontalHeader());
//    set(tr("table_header_sizes"),tr("column%1").arg(logicalIndex),newSize );    
}


void dUserWindow::searchWidgetUpdate()
{
    searchTextChanged( searchLineEdit->text() );    
};


