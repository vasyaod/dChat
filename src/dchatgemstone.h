#ifndef DCHATGEMSTONE_H
#define DCHATGEMSTONE_H

#include <QtGui>

class dManager;
class dChatApplication;
class dSetting;
class dChatPluginInterface;
class dUserWindow;
class dWindowFrame;

// Класс предоставляет интерфейс взаимодействия с основой чата.
class dChatInterface
{
    private:
        dChatApplication *application;
    public:
        dChatInterface();
    // Возвращает указатель на менеджера чата.
        virtual dManager *manager();
    // Возвращает указатель на корень настроек.
        virtual dSetting *settingGeneral();
    // Возвращает указатель на узел настройки плагинов.
        virtual dSetting *settingPlugins();
    // Возвращает ссылку на список загруженных плагинов.
        virtual QList<dChatPluginInterface*> &pluginList();
        
};

// Интерфейс взаимодействия с главным окном чат.
class dUserWindowInterface
{
    private:
        dUserWindow *userWindow;
    public:
        dUserWindowInterface();
    // Метод возвращает указатель на виджет главного окна.
        virtual QMainWindow *mainWindow();
    // Возвращает указатель на рамку окна.
        virtual dWindowFrame *windowFrame();
    // Указатели на различные меню...
    // Меню со списком окон.
        virtual QMenu *windowsMenu();
    // Меню для плагинов.
        virtual QMenu *pluginsMenu();
    // Меню со списком локальных пользователей.
        virtual QMenu *usersMenu();

    // Указазатель на тулс бар с кнопками окон.
        virtual QToolBar *windowToolBar();
};

// Интерфейс позволяет помещать дополнительные действия(пункты) в контекстное
// меню... которое всплывает при нажатии правой клавиши мыши на каком-либо
// пользователе.
class dContextUserMenuInterface
{
    private:
        dChatApplication *application;
    public:
        dContextUserMenuInterface();
        virtual void addWidget( QWidget *_widget );
        virtual void removeWidget( QWidget *_widget );
        
        virtual void addAction( QAction *_action );
        virtual void addActions( QList<QAction*> _actions );
        
};


class dChatGemstone  
{
    public:
        virtual operator dChatInterface*();
        virtual operator dContextUserMenuInterface*();
        virtual operator dUserWindowInterface*();
};

#endif // DCHATGEMSTONE_H

