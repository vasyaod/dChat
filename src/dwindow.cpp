#include "dwindow.h"
#include "dchatapplication.h"
#include "dsettingwindow.h"

#include "dwindowframe/dwindowframe.h"

dWindow::dWindow( const QString &settingKey, dWindowFrame *_windowFrame, QObject *_parent ):
                    windowFrame(_windowFrame),
                    QObject(_parent)
{
    application = qobject_cast<dChatApplication*>(QApplication::instance());
    
    // Загрузим настройки окна.
    settingWindow = new dSettingWindow(settingKey,application->settingWindow,windowFrame);
    
    // Создадим действие.
    windowAct = new QAction(settingKey, this);
    windowAct->setCheckable(true);
    windowAct->setChecked(settingWindow->toInt(tr("visible"),tr("value"),1));    
    connect(windowAct, SIGNAL(toggled(bool)), this, SLOT(setVisible(bool)));
    connect(this, SIGNAL(hideSignal(bool)), windowAct, SLOT(setChecked(bool)));
    
    // Добавим окно в список окон, а также добавим запись в меню.
    application->addWindow(this);
    application->getWindowMenu()->addAction(windowAct);
    //winTopicShowAct->setShortcut(tr("Ctrl+W"));

};

dWindow::~dWindow()
{
  //  settingWindow->set(tr("visible"),tr("value"),isVisible());
    delete windowAct;
    delete settingWindow;
}

void dWindow::hide()
{
    settingWindow->set(tr("visible"),tr("value"),0);
    emit hideSignal();
    windowFrame->hide();
}
void dWindow::lower()
{
    windowFrame->hide();
}
void dWindow::show()
{
    settingWindow->set(tr("visible"),tr("value"),1);
    windowFrame->show();
    double b = settingWindow->toInt(tr("opacity"),tr("value"),100)+1;
    windowFrame->setWindowOpacity(b/100);
}
void dWindow::setVisible( bool _visible )
{
    if(_visible)
        show();
    else 
        hide();
}
bool dWindow::isVisible () const
{
    return windowFrame->isVisible();
}
void dWindow::setTitle( const QString & _title )
{
    windowFrame->setWindowTitle(_title);
    windowAct->setText(_title);
}
void dWindow::setIcon( const QIcon & _icon )
{
    windowFrame->setWindowIcon(_icon);
    windowAct->setIcon(_icon);
};
void dWindow::start()
{
    if( settingWindow->toInt(tr("visible"),tr("value"),1) )
        show();
};

