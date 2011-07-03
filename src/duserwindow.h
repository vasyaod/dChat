#ifndef DUSERWINDOW_H
#define DUSERWINDOW_H

#include <QtGui>

class dListViewEx;
class dWindowFrame;
class dChatApplication;
class dSetting;
class dSettingUserWin;

class dUserWindow : public QObject
{
    Q_OBJECT
    private:
    // Указатель на объект пиложения....
        dChatApplication *application;
        void makeAction();

    // Указатель на мудреное окно.   
        dWindowFrame *window;
    // Различные действия.
        QAction *allParametersAct;
        QAction *viewBarAct;
        QAction *viewIconAct;
        QAction *viewListAct;
        QAction *viewTableAct;
        QAction *refreshAct;
        QAction *sendMessageAct;
        QAction *sendBeepAct;
        QAction *userInfoAct;
        QAction *userInfoRefreshAct;
        QAction *sendPersonalMassAct;
        QAction *sendMassAct;
        QAction *logWindowAct;

        QActionGroup *viewActGroup;
    
    // Настройки окна.
        dSetting *settingWindow;
        dSettingUserWin* settingUserWindow; // Уже другие.
        
    // Разделитель между таблице(листом) поиска и целым списком.
        QSplitter *splitter;

    // Список действий для контекстного меню.
        QList<QAction *> contextListAct;

    // Методы создают виджеты с различными типами списка пользователей.
        dListViewEx *createBarListView( bool searched = false );
        QListView *createIconView( bool searched = false );
        QListView *createListView( bool searched = false );
        QTableView *createTableView( bool searched = false );
        
    // Строка с числом пользователей..
        QLabel *numberUserLabel;
    // Группа действий с пользователями.
        QActionGroup *usersActionGroup;
    public:
    // Главное окно.....
        QMainWindow *listWidget;

    // Различные меню...
        QMenuBar *menuBar;   // Основное 
        QMenu   *actionsMenu,
                *pluginsMenu,
                *windowMenu;
    // Указатель на меню с пользователями.
        QMenu   *usersMenu;
    // Тулс быры.....
        QToolBar *windowToolBar;
    
    
    // Визуальный список пользователей.
        dListViewEx * userBarListView;
        QListView * userIconView;
        QListView * userListView;
        QTableView * userTableView;
        
    // Списки "найденых" пользователей.
        dListViewEx * searchBarListView;
        QListView * searchIconView;
        QListView * searchListView;
        QTableView * searchTableView;    

    // Различные тулс бары.
        QToolBar *toolbar;
        QToolBar *searchBar;
        QToolBar *numberUserBar;
        
    // Бар для поиска.
        QLineEdit*searchLineEdit;
    // ****
        QWidget *currentUserView;

        dUserWindow( dWindowFrame *_window );
        ~dUserWindow();

        dWindowFrame *getWindowPtr() { return window; };
    
    // Возвращает указатель на меню с локальными пользователями.
        QMenu *getUsersMenu() const { return usersMenu; };
    // Возвращает указатель на меню с локальными пользователями.
        QActionGroup *getUsersActionGroup() const { return usersActionGroup; };
    
    public slots:
    
    // Это одна из самых больших жоп.....
    // Функция вызывается из dUserEx, для того чтобы обновить
    // виджет поика.
        void searchWidgetUpdate();
    
        void closed();
        void minimized();
        void show();
        
    // При выборе листа типа "плитка".
        void viewBarToggled ( bool checked );
        void viewIconToggled ( bool checked );
        void viewListToggled ( bool checked );
        void viewTableToggled ( bool checked );
    // При нажатии на кнопку происходит обновление списка.
        void refreshTriggered ( bool checked = false );
    // При нажатии происходит обновление информации о пользователе.
        void refreshInfoTriggered ( bool checked = false );
    // Вызывается когда нужно показать информацию о пользователе.
        void userInfoTriggered ( bool checked = false );
    // При нажатии кнопки звукового вызова.
        void sendBeepTriggered ( bool checked = false );
    // При нажатии кнопки создания сообщения.
        void sendMessageTriggered ( bool checked = false );
    // При нажатии кнопки посылки массовых сообщений.
        void sendMassTriggered ( bool checked = false );
    // При нажатии кнопки посылки персоональных массовых сообщений.
        void sendPersonalMassTriggered ( bool checked = false );
    // При вызове контекстного меню.
        void customContextMenuRequested ( const QPoint & pos );
    // При изменении строки поиска.
        void searchTextChanged( const QString & );
    // Вызывается при смене числа пользователей...
        void countUserChange( int _count );
    // Слот, реакция на перемещение сплитера.
        void splitterMoved( int pos, int index );
    // Слот, реакция на изменение размеров колонок в таблице,
    // и последующее их сохранение(размеров).
        void tableHeaderResize( int logicalIndex, int oldSize, int newSize );
    // Вызывается при двойном нажатии мыши на списке пользователей.
        void itemDoubleClicked ( const QModelIndex & index );
//        void viewHovered( QAction * action );
};

#endif // DUSERWINDOW_H
