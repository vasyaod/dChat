#include "dchatgemstone.h"
#include "dchatapplication.h"
#include "dsettinggeneral.h"
#include "duserwindow.h"

#include "netex/dmanagerex.h"
//=========================================================================
//                      class dChatInterface
dChatInterface::dChatInterface()
{
    application = qobject_cast<dChatApplication*>(QApplication::instance());
}
dManager *dChatInterface::manager()
{
    return application->get_managerEx();
}
dSetting *dChatInterface::settingGeneral()
{
    return application->settingGeneral;
}
dSetting *dChatInterface::settingPlugins()
{
    return application->settingPlugins;
}
QList<dChatPluginInterface*> &dChatInterface::pluginList()
{
    return application->getPluginsList();
}

//=========================================================================
//                      class dUserWindowInterface
dUserWindowInterface::dUserWindowInterface()
{
    dChatApplication *application = qobject_cast<dChatApplication*>(QApplication::instance());
    userWindow = application->user_window;
}

QMainWindow *dUserWindowInterface::mainWindow()
{
    return userWindow->listWidget;
}

dWindowFrame *dUserWindowInterface::windowFrame()
{
    return userWindow->getWindowPtr();
}
QMenu *dUserWindowInterface::windowsMenu()
{
    return userWindow->windowMenu;
}
QMenu *dUserWindowInterface::pluginsMenu()
{
    return userWindow->pluginsMenu;
}
QMenu *dUserWindowInterface::usersMenu()
{
    return userWindow->usersMenu;
}
QToolBar *dUserWindowInterface::windowToolBar()
{
    return userWindow->windowToolBar;
}

//=========================================================================
//                      class dContextUserMenuInterface
dContextUserMenuInterface::dContextUserMenuInterface()
{
    application = qobject_cast<dChatApplication*>(QApplication::instance());
}
void dContextUserMenuInterface::addWidget( QWidget *_widget )
{
    application->contextUserMenu.addWidget(_widget);
}
void dContextUserMenuInterface::removeWidget( QWidget *_widget )
{
    application->contextUserMenu.removeWidget(_widget);
}
void dContextUserMenuInterface::addAction( QAction *_action )
{
    application->contextUserMenu.addAction(_action);
}
void dContextUserMenuInterface::addActions( QList<QAction*> _actions )
{
    application->contextUserMenu.addActions(_actions);
}

//=========================================================================
//                      class dChatGemstone
dChatGemstone::operator dChatInterface*()
{
    return new dChatInterface();
}
dChatGemstone::operator dContextUserMenuInterface*()
{
    return new dContextUserMenuInterface();
}
dChatGemstone::operator dUserWindowInterface*()
{
    return new dUserWindowInterface();
}


