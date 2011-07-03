#include "../dchatapplication.h"
#include "../dsetting.h"
#include "../dpropertywindow.h"

#include "../netex/dmanagerex.h"
#include "../dwindowframe/dwindowframe.h"

#include "dchannelwindow.h"
#include "dsettingchannel.h"
#include "dmessagetable.h"


class dMessageText : public QTextEdit
{
    private:
        dChatApplication *application;    
    public:
        dMessageText( QWidget * _parent = 0 );
        void addMessage(dPUser _usr, const QString &_msg);
};

dMessageText::dMessageText( QWidget * _parent):
        QTextEdit(_parent)
{
    application = qobject_cast<dChatApplication*>(QApplication::instance());
    setReadOnly( true );    

    QAction *clearAct = new QAction(tr("Очистить"), this);
    clearAct->setIcon(QIcon(tr("pic/new32x32.png")));
    connect(clearAct, SIGNAL(triggered()), this, SLOT(clear()));

    addAction(clearAct);
    setContextMenuPolicy(Qt::ActionsContextMenu);
};

void dMessageText::addMessage(dPUser _usr, const QString &_msg)
{
    QTime time(QTime::currentTime());
    setPlainText(toPlainText()+tr("\n[%2] <%1> ").arg(_usr->get_name()).arg(time.toString())+_msg);
    verticalScrollBar()->setValue( verticalScrollBar()->maximum() );
}

// Изменим немного класс QTextEdit, так как нам надо отлавливать нажатие
// клавиши eNTER.
class dTextEditEx : public QTextEdit
{
    private:
        dChatApplication *application;    
        dChannelWindow *channelWindow;
    public:
        dTextEditEx( dChannelWindow *_channelWindow,  QWidget *_parent=0);
    protected:
        virtual void keyPressEvent ( QKeyEvent * _event );
};

dTextEditEx::dTextEditEx( dChannelWindow *_channelWindow ,QWidget * _parent):
        channelWindow(_channelWindow),
        QTextEdit(_parent)
{
    application = qobject_cast<dChatApplication*>(QApplication::instance());
};
        
void dTextEditEx::keyPressEvent ( QKeyEvent * _event )
{
    if ( _event->key() == Qt::Key_Return )
    {
        dManager *manager = application->get_managerEx();
        manager->send_msg_channel(manager->get_users(),toPlainText(),manager->get_main_user() );
        
        channelWindow->addMessage( manager->get_main_user(), toPlainText());
        document()->clear();
    }
    else if ( _event->key() == Qt::Key_Backspace && _event->modifiers() == Qt::CTRL )
        setPlainText(application->keyConverter(toPlainText()));
    else
        QTextEdit::keyPressEvent(_event);
}

dChannelWindow::dChannelWindow( dWindowFrame *_window ):
        dWindow(tr("channel_window"),_window),
        window(_window)
{
    setTitle(tr("Окно канала"));
    setIcon(QIcon(tr("pic/channel64x64.png")));
    getSettingWindow()->setTitle(tr("Настройки стиля окна канала(channel)."));
    getWindowAct()->setShortcut(tr("Ctrl+E"));
    
    application = qobject_cast<dChatApplication*>(QApplication::instance());
    setParent(application);
    
    window->setMinButton(false);        // Уберем кнопочку "свернуть".    
 //   window->setMaxButton(false);        // Уберем кнопочку "развернуть".    
        
    settingChannel = new dSettingChannel(tr("channel_window_other"),application->settingWindow,this);
    settingChannel->setTitle(tr("Окно канала"));
    settingChannel->setIcon(QIcon(tr("pic/channel64x64.png")));
    
    settingAct = new QAction(tr("Настройки окна канала"), this);
    settingAct->setIcon(QIcon(tr("pic/channel64x64.png")));
    connect(settingAct, SIGNAL(triggered(bool)), this, SLOT(settingToggled(bool)));
    
    
    splitter = new QSplitter(Qt::Vertical);
    stackedWidget = new QMainWindow();
    messageText = 0;
    messageTable = 0;
    setViewMode(settingChannel->isTableView());

    splitter->addWidget(stackedWidget);

    editorMessage = new dTextEditEx(this,splitter);
    splitter->addWidget(editorMessage);
    
    window->setCentralWidget(splitter);
    connect(window, SIGNAL(closed()), this, SLOT(hide()));
    
    QList<int> sizes; 
    for( int i=0; i<2; i++)
         sizes << settingChannel->toInt(tr("splitter_sizes"),tr("size%1").arg(i),int(splitter->width()/2));
    splitter->setSizes(sizes);
}

dChannelWindow::~dChannelWindow()
{
    QList<int> sizes = splitter->sizes(); 
    for( int i=0; i<sizes.size(); i++)
    {
        settingChannel->set(tr("splitter_sizes"),tr("size%1").arg(i),tr("%1").arg(sizes[i]));
    }
};
void dChannelWindow::addMessage( dPUser _usr, const QString &_msg)
{
    if( settingChannel->isTableView() )
        messageTable->addMessage( _usr, _msg);
    else
        messageText->addMessage( _usr, _msg);
}

void dChannelWindow::addMessageMe( dPUser _usr, const QString &_msg)
{
    if( settingChannel->isTableView() )
        messageTable->addMessage( _usr, _msg);
    else
        messageText->addMessage( _usr, _msg);
}
void dChannelWindow::addNameToEdit( const QString &_name )
{
    //Сохраним текущий курсор.
    QTextCursor textCursor = editorMessage->textCursor();
        
    QString name = _name;
    editorMessage->setPlainText(name+":"+editorMessage->toPlainText());
    editorMessage->setFocus(Qt::OtherFocusReason);
    
    // Добавим к текущей позиции курсора число символов в имени и переместим курсор
    // на новое место.
    textCursor.setPosition(textCursor.position()+_name.size()); 
    editorMessage->setTextCursor(textCursor);        
}

void dChannelWindow::setViewMode( bool isTable )
{
    QAction *separator = new QAction(tr(""),this);
    separator->setSeparator ( true );
    if( isTable )
    {
        if( messageText ) delete messageText;
        messageTable =  new dMessageTable();
        connect(messageTable, SIGNAL(addNameSignal(const QString&)), this, SLOT(addNameToEdit(const QString&)));
        messageTable->setMaximumMessage(settingChannel->toInt(tr("max_message"),tr("value"),30));
        messageTable->setMaximumName(settingChannel->toInt(tr("max_name"),tr("value"),10));
        messageTable->addAction(separator);
        messageTable->addAction(settingAct);
        messageTable->verticalHeader()->addAction(separator);
        messageTable->verticalHeader()->addAction(settingAct);

        stackedWidget->setCentralWidget(messageTable);
    }
    else
    {
        if( messageTable )  delete messageTable;
        messageText = new dMessageText;
        messageText->addAction(separator);
        messageText->addAction(settingAct);

        stackedWidget->setCentralWidget(messageText);
    }
}
void dChannelWindow::settingToggled( bool _clickable )
{
    application->property_window->goSetting(settingChannel);
}

