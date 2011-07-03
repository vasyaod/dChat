#include "dmessageeditor.h"

#include "../netex/dmanagerex.h"

#include "dsettingmessageeditor.h"
#include "../dchatapplication.h"

class dMessageTextEdit: public QTextEdit
{
    public:
        dMessageTextEdit( QWidget *_parent=0):QTextEdit(_parent){};
    protected:
        virtual void keyPressEvent ( QKeyEvent * _event );
};

void dMessageTextEdit::keyPressEvent ( QKeyEvent * _event )
{
    if ( _event->key() == Qt::Key_Backspace && _event->modifiers() == Qt::CTRL )
    {
        dChatApplication *application = qobject_cast<dChatApplication*>(QApplication::instance());
        setPlainText(application->keyConverter(toPlainText()));
    }
    else
        QTextEdit::keyPressEvent(_event);
}

dMessageEditor::dMessageEditor( dSettingMessageEditor *_settingMessageEditor,
                                QList<dPUser> _to, 
                                dPUser _from, 
                                const QString &_msg,
                                const QString &_title, 
                                typeMessage _tm,
                                bool _showed,
                                bool _html,
                                QWidget *_parent):
        settingMessageEditor(_settingMessageEditor),
        to(_to), 
        from(_from),
        showed(_showed),
        QMainWindow(_parent)
{
    application = qobject_cast<dChatApplication*>(QApplication::instance());
    setWindowTitle(_title); 
    setWindowIcon(QIcon(tr("pic/feather64x64.png"))); 
   // Востановим размеры окна.
    resize( settingMessageEditor->toSize(tr("size"),QSize(300,200)) );            
   
    QWidget * messageEditorWidget =  new QWidget();
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(1);
    layout->setSpacing(5);

// --------------------------- СОЗДАЕМ ДЕЙСТВИЯ ---------------------------------------
    
    actionUndo = new QAction(QIcon("pic/editundo.png"), tr("&Назад"), this);
    actionUndo->setShortcut(Qt::CTRL + Qt::Key_Z);
    actionRedo = new QAction(QIcon("pic/editredo.png"), tr("В&перед"), this);
    actionRedo->setShortcut(Qt::CTRL + Qt::Key_Y);
    actionCut = new QAction(QIcon("pic/editcut.png"), tr("&Вырезать"), this);
    actionCut->setShortcut(Qt::CTRL + Qt::Key_X);
    actionCopy = new QAction(QIcon("pic/editcopy.png"), tr("&Копировать"), this);
    actionCopy->setShortcut(Qt::CTRL + Qt::Key_C);
    actionPaste = new QAction(QIcon("pic/editpaste.png"), tr("Вст&авить"), this);
    actionPaste->setShortcut(Qt::CTRL + Qt::Key_V);
    
    actionTextBold = new QAction(QIcon("pic/textbold.png"), tr("&Bold"), this);
    actionTextBold->setShortcut(Qt::CTRL + Qt::Key_B);
    QFont bold;
    bold.setBold(true);
    actionTextBold->setFont(bold);
    connect(actionTextBold, SIGNAL(triggered()), this, SLOT(textBold()));
    actionTextBold->setCheckable(true);

    actionTextItalic = new QAction(QIcon("pic/textitalic.png"), tr("&Italic"), this);
    actionTextItalic->setShortcut(Qt::CTRL + Qt::Key_I);
    QFont italic;
    italic.setItalic(true);
    actionTextItalic->setFont(italic);
    connect(actionTextItalic, SIGNAL(triggered()), this, SLOT(textItalic()));
    actionTextItalic->setCheckable(true);

    actionTextUnderline = new QAction(QIcon("pic/textunder.png"), tr("&Underline"), this);
    actionTextUnderline->setShortcut(Qt::CTRL + Qt::Key_U);
    QFont underline;
    underline.setUnderline(true);
    actionTextUnderline->setFont(underline);
    connect(actionTextUnderline, SIGNAL(triggered()), this, SLOT(textUnderline()));
    actionTextUnderline->setCheckable(true);
    
    QActionGroup *grp = new QActionGroup(this);
    connect(grp, SIGNAL(triggered(QAction *)), this, SLOT(textAlign(QAction *)));

    actionAlignLeft = new QAction(QIcon("pic/textleft.png"), tr("&Left"), grp);
    actionAlignLeft->setShortcut(Qt::CTRL + Qt::Key_L);
    actionAlignLeft->setCheckable(true);
    actionAlignCenter = new QAction(QIcon("pic/textcenter.png"), tr("C&enter"), grp);
    actionAlignCenter->setShortcut(Qt::CTRL + Qt::Key_E);
    actionAlignCenter->setCheckable(true);
    actionAlignRight = new QAction(QIcon("pic/textright.png"), tr("&Right"), grp);
    actionAlignRight->setShortcut(Qt::CTRL + Qt::Key_R);
    actionAlignRight->setCheckable(true);
    actionAlignJustify = new QAction(QIcon("pic/textjustify.png"), tr("&Justify"), grp);
    actionAlignJustify->setShortcut(Qt::CTRL + Qt::Key_J);
    actionAlignJustify->setCheckable(true);

    QPixmap pix(16, 16);
    pix.fill(Qt::black);
    actionTextColor = new QAction(pix, tr("&Color..."), this);
    connect(actionTextColor, SIGNAL(triggered()), this, SLOT(textColor()));

    actionSave = new QAction(QIcon("pic/filesave.png"), tr("&Сохранить..."), this);
    actionSave->setShortcut(Qt::CTRL + Qt::Key_S);
    connect(actionSave, SIGNAL(triggered()), this, SLOT(saveMessage()));

    comboFont = new QComboBox();
    comboFont->setEditable(true);
    QFontDatabase db;
    comboFont->addItems(db.families());
    connect(comboFont, SIGNAL(activated(const QString &)),
            this, SLOT(textFamily(const QString &)));
    comboFont->setCurrentIndex(comboFont->findText(QApplication::font().family()));

    comboSize = new QComboBox();
    comboSize->setObjectName("comboSize");
    comboSize->setEditable(true);

    foreach(int size, db.standardSizes())
        comboSize->addItem(QString::number(size));

    connect(comboSize, SIGNAL(activated(const QString &)),
            this, SLOT(textSize(const QString &)));
    comboSize->setCurrentIndex(comboSize->findText(QString::number(QApplication::font()
                                                                   .pointSize())));

// --------------------------- СОЗДАЕМ ТУЛС-БЫРЫ ---------------------------------------
    QToolBar *fromToolBar = new QToolBar (tr("Панель \"От\""));
    fromToolBar->setObjectName(tr("toolbar_from"));
        QLabel *fromLabel = new QLabel(tr("Oт: ") );
        fromToolBar->addWidget( fromLabel ); 
        QComboBox *fromComboBox = new QComboBox;
        fromComboBox->addItem(tr(" %1 (IP: %2)").arg(from->get_name().left(30)).arg(from->get_ip().toString()));
        fromComboBox->setItemIcon(0,QIcon(from->get_avatar()));
        fromToolBar->addWidget( fromComboBox ); 
    addToolBar(fromToolBar);
    addToolBarBreak();
    QToolBar *toToolBar = new QToolBar (tr("Панель \"Для\""));
    toToolBar->setObjectName(tr("toolbar_to"));
        QLabel *toLabel = new QLabel(tr("Для: ") );
        toToolBar->addWidget( toLabel ); 
        QComboBox *toComboBox = new QComboBox;
        foreach( dPUser usr, _to)
        {
            toComboBox->addItem(tr(" %1 (IP: %2)").arg(usr->get_name().left(30)).arg(usr->get_ip().toString()));
            toComboBox->setItemIcon(toComboBox->count()-1,QIcon(usr->get_avatar()));
        }
        toToolBar->addWidget( toComboBox ); 
    addToolBar(toToolBar);
    addToolBarBreak();
    QToolBar *typeToolBar = new QToolBar (tr("Панель \"Тип сообщения\""));
    typeToolBar->setObjectName(tr("toolbar_msg_type"));
        QLabel *typeLabel = new QLabel(tr("Тип сообщения: ") );
        typeToolBar->addWidget( typeLabel ); 
        typeComboBox = new QComboBox;
        typeComboBox->addItem(tr("Личное сообщение"));
        typeComboBox->addItem(tr("Массовое сообщение"));
        if( _tm == msg_personal )
            typeComboBox->setCurrentIndex(0);
        else
            typeComboBox->setCurrentIndex(1);
        typeToolBar->addWidget( typeComboBox ); 
    addToolBar(typeToolBar);
    addToolBarBreak();
    QToolBar *editToolBar = new QToolBar(tr("Панель редактирования"));
    editToolBar->setObjectName(tr("toolbar_edit"));
        editToolBar->addAction(actionUndo);
        editToolBar->addAction(actionRedo);
        editToolBar->addAction(actionCut);
        editToolBar->addAction(actionCopy);
        editToolBar->addAction(actionPaste);
    addToolBar(editToolBar);    
    addToolBarBreak();
    QToolBar *formatToolBar = new QToolBar(tr("Панель форматирования"));
    formatToolBar->setObjectName(tr("toolbar_format"));
        formatToolBar->addAction(actionTextBold);
        formatToolBar->addAction(actionTextItalic);
        formatToolBar->addAction(actionTextUnderline);
        formatToolBar->addActions(grp->actions());
        formatToolBar->addAction(actionTextColor);
    addToolBar(formatToolBar);
    addToolBarBreak();
    QToolBar *fontToolBar = new QToolBar(tr("Панель шрифтов"));
    fontToolBar->setObjectName(tr("toolbar_font"));
        fontToolBar->addWidget(comboFont);
        fontToolBar->addWidget(comboSize);
    addToolBar(fontToolBar);  
// --------------------------- СОЗДАЕМ МЕНЮ ---------------------------------------
    QMenuBar *menu = new QMenuBar();
      QMenu *messageMenu = new QMenu(tr("&Сообщение"));
        messageMenu->addAction(actionSave);
      menu->addMenu(messageMenu);
      QMenu *editMenu = new QMenu(tr("&Правка"));
        editMenu->addAction(actionUndo);
        editMenu->addAction(actionRedo);
        editMenu->addSeparator();
        editMenu->addAction(actionCut);
        editMenu->addAction(actionCopy);
        editMenu->addAction(actionPaste);
      menu->addMenu(editMenu);
      QMenu *viewMenu = new QMenu(tr("&Вид"));
        viewMenu->addAction(fromToolBar->toggleViewAction());
        viewMenu->addAction(toToolBar->toggleViewAction());
        viewMenu->addAction(typeToolBar->toggleViewAction());      
        viewMenu->addAction(editToolBar->toggleViewAction());      
        viewMenu->addAction(formatToolBar->toggleViewAction());      
        viewMenu->addAction(fontToolBar->toggleViewAction());      
      menu->addMenu(viewMenu);
      QMenu *formatMenu = new QMenu(tr("Фор&мат"));
        formatMenu->addAction(actionTextBold);
        formatMenu->addAction(actionTextItalic);
        formatMenu->addAction(actionTextUnderline);
        formatMenu->addSeparator();
        formatMenu->addActions(grp->actions());
        formatMenu->addSeparator();
        formatMenu->addAction(actionTextColor);
      menu->addMenu(formatMenu);
    setMenuBar(menu);
// --------------------------------------------------------------------------------
  // Подправим предыдущее сообщение.
//    oldMsg += _msg;

    QTextDocument msgDocument;
    if(_html)
        msgDocument.setHtml(_msg);
    else
        msgDocument.setPlainText(_msg);
   
    if( !_msg.isEmpty() )
    {
        QTextCursor cursor(&msgDocument);
        QTextBlock currentBlock = msgDocument.begin();
        while (currentBlock.isValid()) {
            if(currentBlock.isValid() )
            {
                cursor.setPosition(currentBlock.position());
                cursor.insertText(">");
            }
            currentBlock = currentBlock.next();
        }
        cursor.movePosition(QTextCursor::End);
        cursor.insertBlock();
    }
    oldMsg = msgDocument.toHtml();
    
  // Создаем поле с текстовым сообщением.
    newMessageTextEdit = new dMessageTextEdit();
    if( settingMessageEditor->getQuoting() == 0 )
    {
            splitter = new QSplitter(Qt::Vertical);
            oldMessageTextEdit = new QTextEdit();
            oldMessageTextEdit->setReadOnly(true);
            oldMessageTextEdit->setHtml(oldMsg);
            
            splitter->addWidget(oldMessageTextEdit);
            splitter->addWidget(newMessageTextEdit);
            
        // Востанавливаем размеры сплидера.....
            QList<int> sizes; 
            for( int i=0; i<2; i++)
                 sizes << settingMessageEditor->toInt(tr("splitter_sizes"),tr("size%1").arg(i),int(splitter->width()/2));
            splitter->setSizes(sizes);
            connect(splitter, SIGNAL(splitterMoved( int,int)), this, SLOT(splitterMoved(int,int)));
            
        layout->addWidget(splitter);
    }
    else
    {
        // Подправим предыдущее сообщение, если оно есть....
        newMessageTextEdit->setHtml(oldMsg);
        layout->addWidget(newMessageTextEdit);
        oldMsg = tr("");
    }

        QHBoxLayout *layoutButton = new QHBoxLayout;
        layoutButton->setSpacing(5);
        QPushButton *sendButton = new QPushButton(tr("Отправить"));
        sendButton->setDefault(true);
    //   skinPushButton->setIcon(QIcon(tr("pic/open32x32.png")));
        connect(sendButton, SIGNAL(clicked()), this, SLOT(clickedSendButton()));
        layoutButton->addWidget(sendButton); 
        QPushButton *closeButton = new QPushButton(tr("Закрыть"));
        connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
        layoutButton->addWidget( closeButton ); 
        layoutButton->addStretch ( 1 );
    layout->addItem(layoutButton);
    
    messageEditorWidget->setLayout(layout); 
    setCentralWidget(messageEditorWidget);
    // Востановим параметры окна.
    
    QByteArray state = settingMessageEditor->toByteArray(tr("message_editor_state"),saveState());
    restoreState(state);

    // Выравнием размеры некоторых виджетов...
    fromLabel->setMinimumWidth(toLabel->width());
    if( toComboBox->width() < fromComboBox->width() )
        toComboBox->setMinimumWidth(fromComboBox->width());
    else
        fromComboBox->setMinimumWidth(toComboBox->width());

    if(showed == false)
    {
        activeWindow = QApplication::activeWindow();
        setWindowState(Qt::WindowMinimized);
        lower();
    }
    show();
    newMessageTextEdit->setFocus(Qt::OtherFocusReason);
    
    
    if( settingMessageEditor->getQuoting() == 0 )
    {
        //Перемещаем курсор в конец сообщения.
        QTextCursor textCursor(oldMessageTextEdit->document());
        textCursor.movePosition(QTextCursor::End);
        oldMessageTextEdit->setTextCursor(textCursor);        
        oldMessageTextEdit->verticalScrollBar()->setValue( oldMessageTextEdit->verticalScrollBar()->maximum() );
    }
    else
    {
        QTextCursor textCursor(newMessageTextEdit->document());
        textCursor.movePosition(QTextCursor::End);
        newMessageTextEdit->setTextCursor(textCursor);        
        newMessageTextEdit->verticalScrollBar()->setValue( newMessageTextEdit->verticalScrollBar()->maximum() );
    }

    connect(actionUndo, SIGNAL(triggered()), newMessageTextEdit->document(), SLOT(undo()));
    connect(actionRedo, SIGNAL(triggered()), newMessageTextEdit->document(), SLOT(redo()));
    connect(actionCut, SIGNAL(triggered()), newMessageTextEdit, SLOT(cut()));
    connect(actionCopy, SIGNAL(triggered()), newMessageTextEdit, SLOT(copy()));
    connect(actionPaste, SIGNAL(triggered()), newMessageTextEdit, SLOT(paste()));

};

dMessageEditor::~dMessageEditor()
{
    // Сохраним параметры окна.
    settingMessageEditor->set(tr("message_editor_state"),saveState());    
    // Сохраним размеры окна.
    settingMessageEditor->set(tr("size"),size());
}
void dMessageEditor::closeEvent ( QCloseEvent * _event )
{
    QWidget::closeEvent(_event);
    delete this;
};

void dMessageEditor::clickedSendButton()
{
    QTextDocument* msgDocument = newMessageTextEdit->document();
    QTextCursor cursor(msgDocument);
    cursor.movePosition(QTextCursor::Start);
    cursor.insertFragment(QTextDocumentFragment::fromHtml(oldMsg));
    
    QList<dPUser> users = application->get_managerEx()->get_users();
    foreach( dPUser usr, to)
    {   
        if( users.contains(usr) )        
        {
            QString msg;

            if( usr->get_xml_protocol() )
                msg = msgDocument->toHtml();
            else
            {
                msg = msgDocument->toPlainText();
//                msg.replace(QChar(10),tr("\x0D")+tr("\x0A"));
            }
                
            if( typeComboBox->currentIndex()  == 0 )
                usr->send_msg(msg,from, usr->get_xml_protocol()? true:false );
            if( typeComboBox->currentIndex()  == 1 )
                usr->send_msg_mass(msg,from, usr->get_xml_protocol()? true:false );
            usr->send_auto_answer(from);
        }
    }

    close();
}

void dMessageEditor::keyPressEvent ( QKeyEvent * _event )
{
    if(_event->key() == Qt::Key_Return && _event->modifiers() == Qt::ControlModifier)
        clickedSendButton();
    if ( _event->key() == Qt::Key_Backspace && _event->modifiers() == Qt::CTRL )
        newMessageTextEdit->setPlainText(application->keyConverter(newMessageTextEdit->toPlainText()));
};    

bool dMessageEditor::event ( QEvent * _event )
{
  /*  if( _event->type() == QEvent::WindowActivate && showed == false)
    {
        showed = true;
        //activeWindow->activateWindow();
        return true;
    }
    */
    return QMainWindow::event(_event);
}

//////////////////////////////////////////////////////////////
// Слот, реакция на перемещение сплитера.
void dMessageEditor::splitterMoved( int,int )
{
    // Сохраняем размеры сплидера.....
    QList<int> sizes = splitter->sizes(); 
    for( int i=0; i<sizes.size(); i++)
    {
        settingMessageEditor->set(tr("splitter_sizes"),tr("size%1").arg(i),tr("%1").arg(sizes[i]));
    }
}

void dMessageEditor::textBold()
{
    newMessageTextEdit->setFontWeight(actionTextBold->isChecked() ? QFont::Bold : QFont::Normal);
}

void dMessageEditor::textUnderline()
{

    newMessageTextEdit->setFontUnderline(actionTextUnderline->isChecked());
}

void dMessageEditor::textItalic()
{
    newMessageTextEdit->setFontItalic(actionTextItalic->isChecked());
}

void dMessageEditor::textAlign(QAction *a)
{
    if (a == actionAlignLeft)
        newMessageTextEdit->setAlignment(Qt::AlignLeft);
    else if (a == actionAlignCenter)
        newMessageTextEdit->setAlignment(Qt::AlignHCenter);
    else if (a == actionAlignRight)
        newMessageTextEdit->setAlignment(Qt::AlignRight);
    else if (a == actionAlignJustify)
        newMessageTextEdit->setAlignment(Qt::AlignJustify);
}

void dMessageEditor::textFamily(const QString &f)
{
    newMessageTextEdit->setFontFamily(f);
}

void dMessageEditor::textSize(const QString &p)
{
    newMessageTextEdit->setFontPointSize(p.toFloat());
}

void dMessageEditor::textColor()
{
    QColor col = QColorDialog::getColor(newMessageTextEdit->textColor(), this);
    if (!col.isValid())
        return;
    newMessageTextEdit->setTextColor(col);

    QPixmap pix(16, 16);
    pix.fill(col);
    actionTextColor->setIcon(pix);
}

void dMessageEditor::saveMessage()
{
    QString fn = QFileDialog::getSaveFileName(this, tr("Сохранить сообщение..."),
                                              QString(), tr("HTML-Files (*.htm *.html);;All Files (*)"));
    if (!fn.isEmpty()) {
        QFile file(fn);
        if (!file.open(QFile::WriteOnly))
            return;
        QTextStream ts(&file);
        ts.setCodec(QTextCodec::codecForLocale());
        ts << newMessageTextEdit->document()->toHtml();
    }
}

