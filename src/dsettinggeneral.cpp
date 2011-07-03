#include "dsettinggeneral.h"

dSettingGeneral::dSettingGeneral( QDomElement &_element ):
            dSetting(tr("general"),_element )
{ 
    setTitle(tr("Лицензия"));
    setIcon(QIcon(tr("pic/gear64x64.png")));
    QApplication::setApplicationName( get(tr("title"),tr("value"),tr("dChat")) );
};

dSettingGeneral::~dSettingGeneral()
{
    // Удалим све настройки...
    QList<dSetting*> _children = children();
    foreach( dSetting* child, _children )
        delete child;
        
    // сохраним файл настроек...
    saveSetting();
};

QWidget *dSettingGeneral::createWidget()
{ 
    QDomElement licenseElement = element.firstChildElement(tr("license"));
    QDomElement titleElement = element.firstChildElement(tr("title"));
    QDomElement versionElement = element.firstChildElement(tr("version"));
    QDomElement authorElement = element.firstChildElement(tr("author"));
    QDomElement emailElement = element.firstChildElement(tr("email"));
    QDomElement logoElement = element.firstChildElement(tr("logo"));
    QDomElement qtLogoElement = element.firstChildElement(tr("qt_logo"));
    QDomElement codeBlockLogoElement = element.firstChildElement(tr("codeblock_logo"));
    
    QWidget * widget =  new QWidget();
    
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(1);
    layout->setSpacing(2);
    
    QHBoxLayout *layoutInfo = new QHBoxLayout;
        layoutInfo->setSpacing(1);
        layout->setAlignment(Qt::AlignLeft);
        QLabel *labelLogo = new QLabel();
        labelLogo->setPixmap(QPixmap(logoElement.text()));
        layoutInfo->addWidget(labelLogo);   
        QLabel *labelInfo = new QLabel( tr("Программа: %1 <br>Версия: %2<br> Автор: %3 <br>e-mail: %4 <>").
                                    arg(titleElement.text() ).
                                    arg(versionElement.text()).
                                    arg(authorElement.text()).
                                    arg(emailElement.text()));
        layoutInfo->addWidget( labelInfo);   
        layoutInfo->addStretch ( 1 );            
    layout->addItem( layoutInfo );

    QHBoxLayout *layoutCodeBlockInfo = new QHBoxLayout;
        layoutCodeBlockInfo->setSpacing(1);
        QLabel *labelCodeBlockLogo = new QLabel();
        labelCodeBlockLogo->setPixmap(QPixmap(codeBlockLogoElement.text()));
        layoutCodeBlockInfo->addWidget(labelCodeBlockLogo);   
        QLabel *labelCodeBlockInfo = new QLabel( tr("При разработке использовалось IDE Code::Blocks<br>Компилятор Gcc.<br><i>See http://www.codeblocks.org/</i>"));
        layoutCodeBlockInfo->addWidget(labelCodeBlockInfo);   
        layoutCodeBlockInfo->addStretch ( 1 );        
    layout->addItem( layoutCodeBlockInfo );

    QHBoxLayout *layoutQtInfo = new QHBoxLayout;
        layoutQtInfo->setSpacing(1);
        QLabel *labelQtLogo = new QLabel();
        labelQtLogo->setPixmap(QPixmap(qtLogoElement.text()));
        layoutQtInfo->addWidget(labelQtLogo);   
        QLabel *labelQtInfo = new QLabel( tr("Эта программа использует Qt Open Source Edition version 4.0.0<br><i>See http://www.trolltech.com/qt/</i>"));
        layoutQtInfo->addWidget(labelQtInfo);   
        layoutQtInfo->addStretch ( 1 );        
    layout->addItem( layoutQtInfo );
    
    QTextEdit * textEdit = new QTextEdit();
    textEdit->setReadOnly ( true );
    textEdit->setMinimumHeight( 400 );
    QFont font;
    font.setFamily(tr("Courier"));
//    font.setPointSize(8);
    textEdit->setFont(font);
    textEdit->setLineWrapMode( QTextEdit::NoWrap );
    
    QFile file(licenseElement.text());
    if (file.open(QFile::ReadOnly | QFile::Text))
        textEdit->setPlainText(file.readAll());
  // layout->addItem( new QSpacerItem(1,1, QSizePolicy::Expanding, QSizePolicy::Minimum) );

    
    layout->addWidget( textEdit );   
    widget->setLayout(layout); 

    return widget; 
};

void dSettingGeneral::reParsing()
{
    emit reParsingSignal(); 
};



