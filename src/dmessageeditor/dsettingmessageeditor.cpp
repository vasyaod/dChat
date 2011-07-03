#include "dsettingmessageeditor.h"

dSettingMessageEditor::dSettingMessageEditor( const QString &_key, dSetting *_parent ):
            dSetting(_key,_parent )
{ 
    quoting = toInt(tr("quoting"),tr("type"),0);
};

dSettingMessageEditor::~dSettingMessageEditor()
{
    set(tr("quoting"),tr("type"),quoting);
};

QWidget *dSettingMessageEditor::createWidget()
{
    QWidget * widget =  new QWidget();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(1);
    layout->setSpacing(5);
        QGroupBox *groupBox = new QGroupBox();
       // groupBox->setFlat(true);
        
   //     radio1 = new QRadioButton(tr("Не цитировать пред"));
        radio1 = new QRadioButton(tr("Цитировать в отдельном поле"));
        radio2 = new QRadioButton(tr("Цитировать в поле редактирования"));
        
        if( quoting == 0 )
            radio1->setChecked(true);
        else if( quoting == 1 )
            radio2->setChecked(true);

        connect(radio1, SIGNAL(toggled( bool )), this, SLOT(quotingToggled( bool)));
        connect(radio2, SIGNAL(toggled( bool )), this, SLOT(quotingToggled( bool)));
        
        QVBoxLayout *vbox = new QVBoxLayout;
        vbox->addWidget(radio1);
        vbox->addWidget(radio2);
        vbox->addStretch(1);
        groupBox->setLayout(vbox);

    layout->addWidget(groupBox);
    widget->setLayout(layout); 
    return widget; 
};

//При выборе режима цитирования...
void dSettingMessageEditor::quotingToggled ( bool _on )
{
    if( radio1->isChecked() )
        quoting = 0;
    if( radio2->isChecked() )
        quoting = 1;
}; 


