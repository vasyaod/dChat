#ifndef DCHATCPPLICATION_H
#define DCHATCPPLICATION_H

#include <QtGui>
#include <QtXml>

#include "netex/dusersfactory.h"

class dManagerEx;
class dUserWindow;
class dTopicWindow;
class dPropertyWindow;
class dChannelWindow;
class dSettingGeneral; 
class dSetting;
class dWindow;
class dWarningWindow;
class dLogWindow;
class dFriendsWindow;
class dTrayIcon;
class dPUser;
class dSettingMessageEditor;
class dChatPluginInterface;
class dSettingStyle;

class dContextUserMenu: public QObject
{
    Q_OBJECT
    private:
        QList<QAction *> actions;
        QList<QWidget *> widgets;
    public:
        void addWidget( QWidget *_widget );
        void removeWidget( QWidget *_widget );
        
        void addAction( QAction *_action );
//        void removeAction( QAction *_action );
        void addActions( QList<QAction*> _actions );
    
        const QList<QAction *> &get_actions(){ return actions; };
    public slots:
        void destroyedWidget(QObject * obj);
        void destroyedAction(QObject * obj);
};

class dChatApplication : public QApplication
{
    Q_OBJECT
    private:
    // Меню содержащее список окон с рамками.
        QMenu *windowMenu;
    // Список окон чата с "рамками"
        QList<dWindow*> windowList;
    // Указатель на объект работы с иконкой в трее....
        dTrayIcon *trayIcon;
    // Указатель на менеджера чата.
        dManagerEx      *chat_manager;
    // XML-ный документ с настройками чата.
        QDomDocument settingDocument; 
    // Метод открывает файл с настройками.
        QDomElement openSettingFile( const QString & _filename);
    // Метод загружает таблиицу символов из файла настроек.
        void loadKeyMap();
    // Карта клавиш...
        QMap<QChar,QChar> keyMap;
    
    // Контекстное меню... при клике на иконку в трее...
        QAction *settingDChatAct,
                *raiseDChatAct,
                *quitDChatAct;
        
        QList<dChatPluginInterface*> pluginsList;
    public:
    
    // Возвращает ссылку на список плагинов...
        QList<dChatPluginInterface*> &getPluginsList(){ return pluginsList; };
    // Контекстное меню.. для списка пользовотелей....
        dContextUserMenu contextUserMenu;
    // Преобразователь текста... при неправельном написании....
    // с английского на русский... и обратно....
        QString keyConverter( const QString &_value );
        
    //  Определим перечисление, тип которого будет указан при возникновении 
    // исключения.
        enum dApplicationError{  plugin_load_error,
                                 setting_parser_error};
        
        dChatApplication(int & argc, char ** argv);
        ~dChatApplication();
    // void start();
    
    // Указатель на основные настроки... вернее это корень дерева всех
    // настроек этого чата.
        dSettingGeneral  *settingGeneral; 
     // Указатель на узел настроек полагинов.
        dSetting *settingPlugins;
    // узел настройки окон.
        dSetting *settingWindow;    
    // -------
        dSettingStyle *settingCommon;
    // Указатель на настройки редактора сообщений.
        dSettingMessageEditor *settingMessageEditor;
        
    // Главное окно (со списком пользователей).
        dUserWindow     *user_window;
    // Окно топика (где показывается заголовок).
        dTopicWindow    *topic_window;   
    // Окно свойств.
        dPropertyWindow *property_window;
    // Окно канала.
        dChannelWindow  *channel_window;
    // Окно всплывающих сообщений.
        dWarningWindow  *warning_window;
    // Окно логов.
        dLogWindow      *log_window;
    // Окно с друзьями.
        dFriendsWindow  *friends_window;
        
        QWidget *trayBarWindow;
        
    // Фабрика пользователей, содержит список возможных типов локальных
    // пользователей, которые можно загрузить с помощью плагина и добавить
    // в фабрику.
        dUsersFactory usersFactory;    
    // Возврашает указатель на менеджера чата.
        dManagerEx *get_managerEx() const { return chat_manager; };
    // Возвращает список окон.
        QList<dWindow*> getWindowList() const { return windowList; };
    //  Добавляет окно в список окон.
        bool addWindow( dWindow* _window);
    // Возвращает меню содержащее список окон.
        QMenu *getWindowMenu() const{ return windowMenu; };
        
    // Титы отправляемых собщений... для редактора сообщений.
        enum typeMessage {
            msg_personal  = 0x1,
            msg_mass = 0x2,
        }; 
    // Метод создает окно с информацией об указанном пользователе.
        QWidget *createUserInfoWindow( dPUser _usr );
    // Метод создает редактор сообщения для пользователя.
    // _from - кто собирается отправить.
    // _to - куда собираются отправить(возможно посылать сообщение нескольким пользователям 
    //          одновременно).
    // _msg - текст предыдущего сообщения.
        QWidget *createMessageEditor( QList<dPUser> _to, 
                                      dPUser _from, 
                                      const QString &_msg = QString(), 
                                      const QString &_title = tr("Сообщение"),
                                      typeMessage _tm = msg_personal, 
                                      bool _showed = true,
                                      bool _html = false);
                                      
        QWidget *createMessageEditor( dPUser _to, 
                                      dPUser _from, 
                                      const QString &_msg = QString(), 
                                      const QString &_title = tr("Сообщение"),
                                      typeMessage _tm = msg_personal, 
                                      bool _showed = true,
                                      bool _html = false);
    

    public slots:
        void showPropertyWindow();
        void showLogWindow();
    
    // Слот срабатывает при клике мыши в иконке в трее....
        void trayIconMouseClick();
    // Когда нужно завершить приложеоние....
        void quitChat();
    
};

#include "dsetting.h"

class dSettingStyle: public dSetting
{
    Q_OBJECT
    private:
        QString styleName;
        QCheckBox *startCheckBox;
        
    public:
    // Свойство указывает нужно ли-завускать чат свернутым...
        bool start_minimized();
        
        dSettingStyle( const QString &_key, dSetting *_parent );
        ~dSettingStyle(){};
        virtual QWidget *createWidget();
    
    public slots:
    // При выборе стиля.
        void styleActivated( const QString & text );
    // Смена состояния старта...    
        void startStateChanged( int _state );
};

#endif // DCHATCPPLICATION_H

