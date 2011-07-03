#include "dsettingtopic.h"
#include "dtopicwindow.h"

dSettingTopic::dSettingTopic( const QString &_key, dSetting *_parent, dTopicWindow *_topicWindow  ):
            topicWindow(_topicWindow),
            dSetting(_key,_parent )
{ 
   font = toFont(tr("font"),QApplication::font()); 
};

dSettingTopic::~dSettingTopic()
{
   // saveSetting();
};

QWidget *dSettingTopic::createWidget()
{
    QWidget * widget =  new QWidget();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(1);
    layout->setSpacing(5);
        QHBoxLayout *layoutButton = new QHBoxLayout;
        layoutButton->setSpacing(5);
        QPushButton *fontButton = new QPushButton(tr("»зменить шрифт"));
        fontButton->setDefault(true);
        connect(fontButton, SIGNAL(clicked()), this, SLOT(clickedFontButton()));
        layoutButton->addWidget(fontButton); 
        QPushButton *stdFontButton = new QPushButton(tr("—бросить на стандартный"));
        connect(stdFontButton, SIGNAL(clicked()), this, SLOT(clickedStdFontButton()));
        layoutButton->addWidget(stdFontButton); 
        layoutButton->addStretch ( 1 );
    layout->addItem(layoutButton);
        
    widget->setLayout(layout); 
    return widget; 
};

void dSettingTopic::clickedFontButton()
{
    bool ok;
    font = QFontDialog::getFont(&ok,font);
    if( ok )
    {
        set(tr("font"),font);
        topicWindow->topicEditor->setFont( font );
        topicWindow->topicEditor->setPlainText(topicWindow->topicEditor->toPlainText());
    }
}

void dSettingTopic::clickedStdFontButton()
{
    font = QApplication::font();
    set(tr("font"),font);
    topicWindow->topicEditor->setFont( font );
    topicWindow->topicEditor->setPlainText(topicWindow->topicEditor->toPlainText());
}


