#include "dtopicwindow.h"
#include "dsettingtopic.h"

#include "../dchatapplication.h"
#include "../dsetting.h"
#include "../dwindowframe/dwindowframe.h"
#include "../netex/dmanagerex.h"

dTopicTextEditEx::dTopicTextEditEx( QWidget * _parent):
        QTextEdit(_parent)
{
    application = qobject_cast<dChatApplication*>(QApplication::instance());
   
    topicEditor = new QWidget();
    topicEditor->setWindowTitle(tr("Редактор заголовка"));
    topicEditor->setWindowIcon(QIcon(tr("pic/book64x64.png")));
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(1);
    layout->setSpacing(5);
    
    topicEditorTextEdit = new QTextEdit();
    layout->addWidget(topicEditorTextEdit); 
    
        QHBoxLayout *layoutButton = new QHBoxLayout;
        layoutButton->setSpacing(5);
        QPushButton *sendButton = new QPushButton(tr("Отправить"));
        sendButton->setDefault(true);
    //   skinPushButton->setIcon(QIcon(tr("pic/open32x32.png")));
        connect(sendButton, SIGNAL(clicked()), this, SLOT(clickedSendButton()));
        layoutButton->addWidget(sendButton); 
        QPushButton *closeButton = new QPushButton(tr("Закрыть"));
        connect(closeButton, SIGNAL(clicked()), topicEditor, SLOT(close()));
        layoutButton->addWidget( closeButton ); 
        layoutButton->addStretch ( 1 );
    
    layout->addItem(layoutButton);
    topicEditor->resize(size());    
    topicEditor->setLayout(layout);

};
void dTopicTextEditEx::clickedSendButton()
{
    send( topicEditorTextEdit->toPlainText() );
    topicEditor->close();
}
void dTopicTextEditEx::keyPressEvent ( QKeyEvent * _event )
{
    if ( _event->key() == Qt::Key_Return )
    {
        send( toPlainText() );
    }
    else if ( _event->key() == Qt::Key_Backspace && _event->modifiers() == Qt::CTRL )
    {
        setPlainText(application->keyConverter(toPlainText()));
//        send(  );
    }
    else
        QTextEdit::keyPressEvent(_event);
}
void dTopicTextEditEx::mouseDoubleClickEvent ( QMouseEvent * _event )
{
    topicEditor->show();
    QTextEdit::mouseDoubleClickEvent(_event);
    topicEditorTextEdit->setPlainText( toPlainText() );
};
void dTopicTextEditEx::send( QString new_topic )
{
    dPUser usr = application->get_managerEx()->get_main_user();
    new_topic = new_topic + tr("(%1)").arg(usr->get_name());
    application->get_managerEx()->send_change_topic(application->get_managerEx()->get_users(),new_topic);
    setPlainText( new_topic);
    usr->set_topic( new_topic );
}

dTopicWindow::dTopicWindow( dWindowFrame *_window, QObject *_parent ):
        dWindow(tr("topic_window"),_window),
        window(_window)
{
    setTitle(tr("Окно заголовка"));
    setIcon(QIcon(tr("pic/book64x64.png")));
    getSettingWindow()->setTitle(tr("Настройки стиля окна заголовка(topic)."));
    getWindowAct()->setShortcut(tr("Ctrl+W"));
    
    application = qobject_cast<dChatApplication*>(QApplication::instance());
    setParent(application);

    window->setMinButton(false);        // Уберем кнопочку "свернуть".    
    
    dSettingTopic *settingTopic = new dSettingTopic(tr("topic_window"),application->settingWindow,this);
    settingTopic->setTitle(tr("Окно заголовка"));
    settingTopic->setIcon(QIcon(tr("pic/book64x64.png")));

    topicEditor = new dTopicTextEditEx();
    topicEditor->setFont(settingTopic->getFont());
    topicEditor->setPlainText(tr(""));
   // topicEditor->setFont(settingTopic->getFont());

    window->setCentralWidget(topicEditor);

    connect(window, SIGNAL(closed()), this, SLOT(hide()));
}

dTopicWindow::~dTopicWindow()
{

};

void dTopicWindow::setTopic( const QString &_topic )
{
    topicEditor->setPlainText(_topic);
}

