#include <QtGui>

#include <iostream.h>

#include "dchatapplication.h"
#include "duserwindow.h"
#include "dpropertywindow.h"
#include "dsettinggeneral.h"
#include "dplugininterface.h"       // Интерфейс плагинов....
#include "dchatgemstone.h"          // Кристал программы...
#include "dsettingplugin.h"         // Настройки плагинов...

#include "netex/dmanagerex.h"   
#include "netex/dsettingusers.h"   
#include "netex/dsettingnet.h"   
#include "netex/dlocaluserex.h"   
#include "netex/dlocalautouserex.h"   

#include "dwindowframe/dwindowframe.h"

#include "dmessageeditor/dmessageeditor.h"
#include "dmessageeditor/dsettingmessageeditor.h"

#include "dchannelwindow/dchannelwindow.h"
#include "dtopicwindow/dtopicwindow.h"
#include "dwarningwindow/dwarningwindow.h"
#include "dlogwindow/dlogwindow.h"
#include "duserinfowindow/duserinfowindow.h"
#include "dfriendswindow/dfriendswindow.h"
#include "dtrayicon/dtrayicon.h"

#include "net/dlocaluser.h"   
#include "net/dservice.h"   

class dTrayBarWindow: public QWidget
{
    private:
        dUserWindow *window;
    public:
        dTrayBarWindow( dUserWindow * _win, QWidget * _parent = 0, Qt::WFlags _f = 0 ):QWidget(_parent,_f),window(_win){};
    
    protected:
        bool event ( QEvent * _event );
     //   virtual void showEvent ( QShowEvent * event );
};

bool dTrayBarWindow::event ( QEvent * _event )
{
    if( _event->type() == QEvent::WindowActivate )
    {
        window->show();
        return false;
    }
    if( _event->type() == QEvent::Close )
    {    
        QApplication::exit(0);
        return false;
    }
}


dChatApplication::dChatApplication(int & argc, char ** argv):
        QApplication(argc, argv)

{

    setQuitOnLastWindowClosed ( false );
    
    QSplashScreen *splashScreen = new QSplashScreen(QPixmap(tr("pic/dchat_logo.png")));
    splashScreen->show();
    // Настроим кодировку.
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

    // Созданим меню куда будут помещаться информация о окнах
    windowMenu = new QMenu(tr("Окно"));
    // Главная иконка приложения.
    QApplication::setWindowIcon(QIcon(tr("pic/gear64x64.png")));

    QDomElement element;
    // Откроем xml файл.
    try // Перехватим исключение....
    {
        element = openSettingFile(tr("setting.xml"));
    }
    catch(...) 
    {
        QMessageBox::critical(0, tr("Error."),
                                 tr("Ошибка при чтении файла настроек."),QMessageBox::Ok,0,0);
        QApplication::exit(-1);
    }
    // Создадим общие свойства, которые буду предком у всех остальных свойств.
    settingGeneral = new dSettingGeneral(element);
    settingGeneral->setTitle(tr("Лицензия"));
    settingGeneral->setIcon(QIcon(tr("pic/gear64x64.png")));  
    // Загрузка карты клавиш.
    cout << "Load map of keys." << endl;    
    splashScreen->showMessage(tr("Load map of keys..."),Qt::AlignLeft | Qt::AlignBottom);
    loadKeyMap();

    // Загрузим плагин с "окном".
    dWindowFrame *window_frame;
    cout << "Load dWindowFrame plugin." << endl;    
    splashScreen->showMessage(tr("Load window plugin..."),Qt::AlignLeft | Qt::AlignBottom);
    QPluginLoader window_plugin(settingGeneral->get(tr("window_plugin"),tr("lib"),tr("dwindowframe.dll")),this);
    window_frame = qobject_cast<dWindowFrame*>(window_plugin.instance());
    if (!window_frame)
    {
       qDebug() << "Load dWindowFrame plagin error.";
       QApplication::exit(-1);
//       throw(dApplicationError(plugin_load_error)); // Вызвать исключение, при збое в загрузке плагина.
    }

#ifdef Q_WS_WIN

    // Загрузим плагин работы с треем.
    cout << "Load dTrayIcon plugin." << endl;    
    splashScreen->showMessage(tr("Load tray plugin..."),Qt::AlignLeft | Qt::AlignBottom);
    QPluginLoader tray_plugin(settingGeneral->get(tr("tray_plugin"),tr("lib"),tr("dtrayicon.dll")),this);
    trayIcon = qobject_cast<dTrayIcon*>(tray_plugin.instance());
    if (!window_frame)
    {
       QMessageBox::critical(0, tr("Error."),
                                tr("Load dTrayIcon plagin error."),QMessageBox::Ok,0,0);
       QApplication::exit(-1);
//       throw(dApplicationError(plugin_load_error)); // Вызвать исключение, при збое в загрузке плагина.
    }
    trayIcon->addIcon(settingGeneral->get(tr("tray_icon"),tr("file"),tr("dchat.ico")),QApplication::applicationName());
    
#endif

    // Создаем узел настройки окон.
    settingWindow = new dSetting(tr("windows"),settingGeneral);
    settingWindow->setTitle(tr("Окна"));
    settingWindow->setIcon(QIcon(tr("pic/win64x64.png")));    
  
    settingCommon = new dSettingStyle(tr("style"),settingWindow);
    settingCommon->setTitle(tr("Общие настройки окон"));

    // Запуск менеджера чата.
    chat_manager = new dManagerEx(this);
    cout << "Manager chat is started." << endl;
    splashScreen->showMessage(tr("Manager chat is started..."),Qt::AlignLeft | Qt::AlignBottom);

    // Создаем узел настройки сети.
    dSettingNet *net_setting = new dSettingNet(settingGeneral);
    net_setting->setTitle(tr("Сетевые"));
    net_setting->setIcon(QIcon(tr("pic/net64x64.png")));   
    
     // Создаем узел настроек полагинов.
    settingPlugins = new dSettingPlugin(tr("plugins"),settingGeneral);
    settingPlugins->setTitle(tr("Плагины"));
    //plugun_setting->setIcon(QIcon(tr("pic/plugin64x64.png")));   

     // Создаем узел настройки редактора сообщений.
    settingMessageEditor = new dSettingMessageEditor(tr("message_editor"),settingWindow);
    settingMessageEditor->setTitle(tr("Редактор сообщений"));
    settingMessageEditor->setIcon(QIcon(tr("pic/feather64x64.png")));   
    
    // Порядок вывода окон не должен быть изменен.
    // Хотя это уже не актуално... можно все... 
    topic_window = new dTopicWindow( window_frame->make() );
    cout << "Topic window is started." << endl;    
    splashScreen->showMessage(tr("Topic window is loaded..."),Qt::AlignLeft | Qt::AlignBottom);
    connect(get_managerEx(), SIGNAL(signal_change_topic(const QString&)), topic_window, SLOT(setTopic( const QString&)));
    connect(get_managerEx(), SIGNAL(signal_current_topic(const QString&)), topic_window, SLOT(setTopic( const QString&)));

    // Порядок вывода окон не должен быть изменен.
    // Хотя это уже не актуално... можно все... 
    channel_window = new dChannelWindow(window_frame->make());
    cout << "Channel window is started." << endl;    
    splashScreen->showMessage(tr("Channel window is loaded..."),Qt::AlignLeft | Qt::AlignBottom);
    connect(get_managerEx(), SIGNAL(signal_msg_channel(dPUser, const QString&)), channel_window, SLOT(addMessage(dPUser, const QString&)));
    connect(get_managerEx(), SIGNAL(signal_msg_channel_me(dPUser, const QString&)), channel_window, SLOT(addMessageMe(dPUser, const QString&)));

    // Окно всплывающих предупруждений.
    warning_window = new dWarningWindow(window_frame->make());
    cout << "Warning window is started." << endl;    
    splashScreen->showMessage(tr("Warning window is loaded..."),Qt::AlignLeft | Qt::AlignBottom);
    connect(get_managerEx(), SIGNAL(signal_msg_channel(dPUser, const QString&)), warning_window, SLOT(slot_msg_channel(dPUser, const QString&)));
    connect(get_managerEx(), SIGNAL(signal_msg_channel_me(dPUser, const QString&)), warning_window, SLOT(slot_msg_channel_me(dPUser, const QString&)));
    connect(get_managerEx(), SIGNAL(signal_change_topic(const QString&)), warning_window, SLOT(slot_change_topic( const QString&)));
    connect(get_managerEx(), SIGNAL(signal_msg_exit( dPUser )), warning_window, SLOT(slot_msg_exit( dPUser )));
    connect(get_managerEx(), SIGNAL(signal_msg_enter( dPUser )), warning_window, SLOT(slot_msg_enter( dPUser )));
    connect(get_managerEx(), SIGNAL(signal_msg_rename( dPUser, const QString &)), warning_window, SLOT(slot_msg_rename( dPUser, const QString &)));

    log_window = new dLogWindow();
    cout << "LOG window is started." << endl;    
    splashScreen->showMessage(tr("LOG window is loaded..."),Qt::AlignLeft | Qt::AlignBottom);
 
    connect(get_managerEx(), SIGNAL(signal_msg_channel(dPUser, const QString&)), log_window, SLOT(slot_msg_channel(dPUser, const QString&)));
    connect(get_managerEx(), SIGNAL(signal_msg_channel_me(dPUser, const QString&)), log_window, SLOT(slot_msg_channel_me(dPUser, const QString&)));
    connect(get_managerEx(), SIGNAL(signal_change_topic(const QString&)), log_window, SLOT(slot_change_topic( const QString&)));
    connect(get_managerEx(), SIGNAL(signal_msg_exit( dPUser )), log_window, SLOT(slot_msg_exit( dPUser )));
    connect(get_managerEx(), SIGNAL(signal_msg_enter( dPUser )), log_window, SLOT(slot_msg_enter( dPUser )));
    connect(get_managerEx(), SIGNAL(signal_msg_rename( dPUser, const QString &)), log_window, SLOT(slot_msg_rename( dPUser, const QString &)));
    connect(get_managerEx(), SIGNAL(signal_msg_beep( dPUser, dPUser)), log_window, SLOT(slot_msg_beep( dPUser, dPUser)));
    connect(get_managerEx(), SIGNAL(signal_msg_mass( dPUser, dPUser, const QString&)), log_window, SLOT(slot_msg_mass( dPUser, dPUser, const QString&)));
    connect(get_managerEx(), SIGNAL(signal_msg_personal( dPUser, dPUser,const QString &)), log_window, SLOT(slot_msg_personal( dPUser, dPUser,const QString &)));
    connect(get_managerEx(), SIGNAL(signal_msg_auto_answer( dPUser, dPUser,const QString &)), log_window, SLOT(slot_msg_auto_answer( dPUser, dPUser,const QString &)));

    // Порядок вывода окон не должен быть изменен.
    // Хотя это уже не актуално... можно все... 
    user_window = new dUserWindow(window_frame);
    cout << "Main window is started." << endl;    
    splashScreen->showMessage(tr("Main window is loaded..."),Qt::AlignLeft | Qt::AlignBottom);
    connect(get_managerEx(), SIGNAL(signal_count_user_change(int)), user_window, SLOT(countUserChange(int)));
    splashScreen->finish(window_frame);

    // Создаем окно которое будет постоянно висеть в трэе
#ifndef Q_WS_WIN
    trayBarWindow = new dTrayBarWindow(user_window);
    trayBarWindow->setWindowTitle(QApplication::applicationName());
    trayBarWindow->move(2000,2000);
    trayBarWindow->setWindowOpacity(0);
    trayBarWindow->resize( 0,0 );
    trayBarWindow->show();
    trayBarWindow->lower();

#else

    // Соединяем иконку в трее с окнами...
    connect(trayIcon, SIGNAL(leftButtonDown()), user_window, SLOT(show()));
    connect(trayIcon, SIGNAL(rightButtonDown()), this, SLOT(trayIconMouseClick()));

    quitDChatAct = new QAction(tr("Выход"), this);
    quitDChatAct->setIcon(QIcon(tr("pic/leg64x64.png")));
    raiseDChatAct = new QAction(tr("Поднять"), this);
    raiseDChatAct->setIcon(QIcon(tr("pic/up64x64.png")));
    settingDChatAct = new QAction(tr("Настройки"), this);
    settingDChatAct->setIcon(QIcon(tr("pic/gear64x64.png")));
    connect(settingDChatAct, SIGNAL(triggered()), this, SLOT(showPropertyWindow()));
    connect(quitDChatAct, SIGNAL(triggered()), this, SLOT(quitChat()));
    connect(raiseDChatAct, SIGNAL(triggered()), user_window, SLOT(show()));
    
#endif

    friends_window = new dFriendsWindow(window_frame->make());
    cout << "Friends window is started." << endl;    
    splashScreen->showMessage(tr("Friends window is loaded..."),Qt::AlignLeft | Qt::AlignBottom);

    // ============= ЗАГРУЖАЕМ ПЛАГИНЫ ==========
    // Создаем кристалл........
    dChatGemstone *chatGemstone = new dChatGemstone; 

    // Шарим по директории с плагинами... и ищем dll-файлы.
    QStringList masks;
    QString log_dir = settingGeneral->get(tr("plugins_dir"),tr("value"),tr("plugins/"));
    masks << tr("*.dll");
    QDir dir(log_dir);
    QStringList files = dir.entryList(masks,QDir::Files);
    foreach( QString filename, files )
    {
        QPluginLoader plugin(log_dir+filename,this);
        dChatPluginInterface *chatPluginInterface = qobject_cast<dChatPluginInterface*>(plugin.instance());
        if (chatPluginInterface)
        {
            if( chatPluginInterface->init(chatGemstone) )
            {
                getPluginsList() << chatPluginInterface;
                QString plugin_str = tr("Loaded plugin: %1").arg(filename);
                qDebug() << plugin_str;
                splashScreen->showMessage(  plugin_str, Qt::AlignLeft | Qt::AlignBottom);
            }
            else
                qDebug() << tr("Can not initialize plugin: %1").arg(filename);
        }
        else
            qDebug() << tr("Can't load plugin: %1").arg(filename);

    }

    //================ СОЗДАЕМ ЛОКАЛЬНЫХ ПОЛЬЗОВАТЕЛЕЙ. =================
    // Добавим стандартный тип локального пользователя в фабрику пользователей.
    usersFactory.addUserCreator(new dLocalAutoUserCreator());
    usersFactory.addUserCreator(new dLocalUserCreator());

     // Создаем узел настройки пользователей.
    dSettingUsers *users_setting = new dSettingUsers(settingGeneral);
    users_setting->setTitle(tr("Пользователи"));
    users_setting->setIcon(QIcon(tr("pic/man64x64.png")));   
    cout << "Local user loaded." << endl;    

    // Загрузка окна свойств.
    property_window = new dPropertyWindow(settingGeneral);
    cout << "Properties window is started." << endl;
    splashScreen->showMessage(tr("Properties window is loaded..."),Qt::AlignLeft | Qt::AlignBottom);

    // Выведем окна на экран.
    user_window->show();
    foreach(dWindow *window, windowList)
        window->start();
        
    if( settingCommon->start_minimized() )
        user_window->minimized();

    delete splashScreen;
};

dChatApplication::~dChatApplication()
{
#ifdef Q_WS_WIN
    disconnect(trayIcon, SIGNAL(leftButtonDown()), user_window, SLOT(show()));
    disconnect(trayIcon, SIGNAL(rightButtonDown()), this, SLOT(trayIconMouseClick()));
#else
    delete trayBarWindow;
#endif

    delete property_window;
    delete user_window;
    delete log_window;
    delete warning_window;
    delete settingCommon;
    // Удалим окна.... пока:
    //  topic window,
    //  channel window,
    //  friends window
    foreach(dWindow *window, getWindowList())
        delete window;
    
    delete chat_manager;
    delete settingGeneral;
#ifdef Q_WS_WIN
    trayIcon->deleteIcon();
#endif
};

void dChatApplication::quitChat()
{
    user_window->minimized();
//    closeAllWindows();
    quit();
}
// Открытие фала с натройками.
QDomElement dChatApplication::openSettingFile( const QString & _filename)
{

    QFile file(_filename);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::critical(0, tr("Cannot read file!"),
                             tr("Cannot read file with setting: %1").arg(_filename),QMessageBox::Ok,0,0);

        throw( dApplicationError(setting_parser_error) );
    }    

    QString errorStr;
    int errorLine;
    int errorColumn;
   
    if (!settingDocument.setContent(&file, true, &errorStr, &errorLine,
                                &errorColumn)) {
        QMessageBox::critical(0, tr("Parse error."),
                                 tr("Parse error at line %1, column %2:\n%3")
                                 .arg(errorLine)
                                 .arg(errorColumn)
                                 .arg(errorStr),QMessageBox::Ok,0,0);
        throw( dApplicationError(setting_parser_error) );
    }
    QDomElement root = settingDocument.documentElement();
    if (root.tagName() != "root") {
        QMessageBox::critical(0, tr("Parse error."),
                                 tr("The file is not an setting file."),QMessageBox::Ok,0,0);
        throw( dApplicationError(setting_parser_error) );
    }    
    
    return root;
};

void dChatApplication::showPropertyWindow() 
{ 
    property_window->show(); 
    property_window->raise(); 
};
void dChatApplication::showLogWindow() 
{ 
    log_window->show(); 
    log_window->raise(); 
};

bool dChatApplication::addWindow( dWindow* _window)
{
    windowList.push_back(_window);
}

void dChatApplication::trayIconMouseClick()
{
    QMenu trayMenu;
    trayMenu.setTearOffEnabled(false);
    trayMenu.addAction(raiseDChatAct);
    trayMenu.addAction(settingDChatAct);
    trayMenu.addSeparator();
    trayMenu.addAction(quitDChatAct);
    trayMenu.exec(QCursor::pos());
}
//////////////////////////////////////////////////////////////
// Метод создает окно с информацией об указанном пользователе.
QWidget *dChatApplication::createUserInfoWindow( dPUser _usr )
{
    if ( !get_managerEx()->get_users().contains(_usr) )
        return NULL;
    return new dUserInfoWindow(_usr);
};
//////////////////////////////////////////////////////////////
// Метод создает редактор сообщения.
// _from - кто собирается отправить.
// _to - куда собираются отправить.
// _msg - текст предыдущего сообщения.
QWidget *dChatApplication::createMessageEditor( dPUser _to, dPUser _from, const QString &_msg, const QString &_title, typeMessage _tm, bool _showed, bool _html)
{
    QList<dPUser> to_users;
    to_users.push_back(_to);
    return createMessageEditor(to_users,_from,_msg,_title,_tm,_showed,_html);
};

QWidget * dChatApplication::createMessageEditor( QList<dPUser> _to, dPUser _from, const QString &_msg, const QString &_title, typeMessage _tm, bool _showed, bool _html )
{
    QWidget *messageEditor;
    if( !_from ) 
        _from = get_managerEx()->get_main_user();
    if( _tm == msg_personal )
          messageEditor = new dMessageEditor(settingMessageEditor,_to,_from,_msg,_title,dMessageEditor::msg_personal,_showed,_html );
    if( _tm == msg_mass )
          messageEditor = new dMessageEditor(settingMessageEditor,_to,_from,_msg,_title,dMessageEditor::msg_mass,_showed,_html );
    return messageEditor;
};



dSettingStyle::dSettingStyle( const QString &_key, dSetting *_parent ):
            dSetting(_key,_parent )
{ 
    setNode(false);
    styleName = get(tr("style"),tr("value"),tr("ICEStyle"));
    styleActivated(styleName);
};

bool dSettingStyle::start_minimized()
{
    return toInt(tr("start_minimized"),tr("value"),0);
}

QWidget *dSettingStyle::createWidget()
{
    QWidget * widget =  new QWidget();
    
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(1);
    layout->setSpacing(5);
 //   layout->addWidget( new QLabel() ); 
    startCheckBox = new QCheckBox(tr("Запускать чат свернутым"));
    connect(startCheckBox, SIGNAL(stateChanged(int)), this, SLOT(startStateChanged(int)));
    startCheckBox->setChecked(start_minimized());
    layout->addWidget ( startCheckBox );
    
    layout->addWidget( new QLabel(tr("Стиль окон:")) ); 
    QComboBox *styleComboBox = new QComboBox();
    styleComboBox->addItems(QStyleFactory::keys());
    styleComboBox->setCurrentIndex ( styleComboBox->findText(styleName) );
    connect(styleComboBox, SIGNAL(activated ( const QString &)), this, SLOT(styleActivated ( const QString &)));    
    layout->addWidget( styleComboBox ); 

    widget->setLayout(layout); 

    return widget; 
};
void dSettingStyle::startStateChanged( int _state )
{
    set(tr("start_minimized"),tr("value"),!_state?0:1);
}

void dSettingStyle::styleActivated ( const QString & _text )
{   
    styleName = _text;
    QApplication::setStyle(QStyleFactory::create(_text));
    set(tr("style"),tr("value"),_text);
}

// Метод загружает таблиицу символов из файла настроек.
void dChatApplication::loadKeyMap()
{
    QDomElement mapElement = settingGeneral->getChildXmlElement(tr("map_of_key"));
    QDomElement keyElement = mapElement.firstChildElement();
    while (!keyElement.isNull()) {
        if ( keyElement.tagName() == tr("key") )
        {
            keyMap.insert(keyElement.attribute(tr("rus"))[0],keyElement.attribute("eng")[0]);
            keyMap.insert(keyElement.attribute(tr("eng"))[0],keyElement.attribute("rus")[0]);
        }
        keyElement = keyElement.nextSiblingElement();
    }
/*    
    QDomElement childElement = mapElement.ownerDocument().createElement("key");
    mapElement.appendChild(childElement);
    childElement.setAttribute(tr("eng"),tr("Z"));
    childElement.setAttribute(tr("rus"),tr("Я"));
//*/
}
QString dChatApplication::keyConverter( const QString &_value )
{
    QString out;
    for( int i = 0; i < _value.size(); i++ )
    {
        out.push_back(keyMap.contains(_value[i])?keyMap.value(_value[i]):_value[i]);
    }
    return out;
}


//========================================================================
//                          class dContextUserMenu
//========================================================================

void dContextUserMenu::addWidget( QWidget *_widget )
{
    widgets << _widget;
    connect(_widget, SIGNAL(destroyed(QObject*)), this, SLOT(destroyedWidget(QObject*)));
    foreach(QAction *action, actions)
        _widget->addAction(action);
    _widget->setContextMenuPolicy(Qt::ActionsContextMenu);
}
void dContextUserMenu::removeWidget( QWidget *_widget )
{
    widgets.removeAll(_widget);
    disconnect(_widget, SIGNAL(destroyed(QObject*)), this, SLOT(destroyedWidget(QObject*)));
    foreach(QAction *action, actions)
        _widget->removeAction(action);
}
void dContextUserMenu::addAction( QAction *_action )
{
    actions.push_back(_action);
    connect(_action, SIGNAL(destroyed(QObject*)), this, SLOT(destroyedAction(QObject*)));
    foreach(QWidget *widget, widgets)
        widget->addAction(_action);    
}

void dContextUserMenu::addActions( QList<QAction*> _actions )
{
    actions << _actions;
    foreach(QAction *action, _actions)
        connect(action, SIGNAL(destroyed(QObject*)), this, SLOT(destroyedAction(QObject*)));
        
    foreach(QWidget *widget, widgets)
        widget->addActions(_actions);  
}

void dContextUserMenu::destroyedWidget(QObject * obj)
{
    QWidget *widget = qobject_cast<QWidget*>(obj);
    if( widget )
        widgets.removeAll(widget);
}

void dContextUserMenu::destroyedAction(QObject * obj)
{
    QAction *action = qobject_cast<QAction*>(obj);
    if( action )
        actions.removeAll(action);
}


