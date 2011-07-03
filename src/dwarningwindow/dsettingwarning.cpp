#include "dsettingwarning.h"

QString dSettingWarning::keys[9] = { tr("persnal_warning"),
                                      tr("mass_warning"),
                                      tr("enter_warning"),
                                      tr("exit_warning"),
                                      tr("beep_warning"),
                                      tr("rename_warning"),
                                      tr("channel_warning"),
                                      tr("channel_me_warning"),
                                      tr("topic_warning")};
                                      
dSettingWarning::dSettingWarning( const QString &_key, dSetting *_parent ):
            dSetting(_key,_parent )
{ 
    windowTimeOut   = toInt(tr("time"),tr("value"),5);
    maxWindow       = toInt(tr("max_window"),tr("value"),7);
};

dSettingWarning::~dSettingWarning()
{
   // saveSetting();
};

QWidget *dSettingWarning::createWidget()
{
    QWidget * widget =  new QWidget();
    int i;
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(1);
    layout->setSpacing(5);
    
        QHBoxLayout *maxWindowLayout = new QHBoxLayout;
        maxWindowLayout->setSpacing(5);
        maxWindowLayout->addWidget( new QLabel("Максимальное число окон, которе может всплыть на экране:") ); 
        QSpinBox *maxWinSpinBox = new QSpinBox;
        maxWinSpinBox->setSingleStep(1);
        maxWinSpinBox->setMinimum(1);
        maxWinSpinBox->setValue(maxWindow);
        connect(maxWinSpinBox, SIGNAL(valueChanged(int)), this, SLOT(maxWindowChanged(int)));
        maxWindowLayout->addWidget( maxWinSpinBox );
        maxWindowLayout->addStretch ( 1 );     
              
    layout->addItem( maxWindowLayout );
            
        QHBoxLayout *timeoutLayout = new QHBoxLayout;
        timeoutLayout->setSpacing(5);
        timeoutLayout->addWidget( new QLabel("Время задержки на экране всплывающего окна:") ); 
        QSpinBox *timeoutSpinBox = new QSpinBox;
        timeoutSpinBox->setSingleStep(1);
        timeoutSpinBox->setMinimum(1);
        timeoutSpinBox->setValue(windowTimeOut);
        connect(timeoutSpinBox, SIGNAL(valueChanged(int)), this, SLOT(timeChanged(int)));
        timeoutLayout->addWidget( timeoutSpinBox );
        timeoutLayout->addStretch ( 1 );           
    layout->addItem( timeoutLayout );
    
    layout->addWidget( new QLabel("<b>Всплывающее окно:</b>"));

        QGridLayout *layoutGrid = new QGridLayout();
        layoutGrid->setSpacing(3);
      //  layoutGrid->setAlignment(Qt::AlignLeft);
        layoutGrid->addWidget ( new QLabel("Личное сообщение: "), 0, 0 ,Qt::AlignRight);
        layoutGrid->addWidget ( new QLabel("Массовое сообщение: "), 1, 0 ,Qt::AlignRight);
        layoutGrid->addWidget ( new QLabel("Вход пользователя в чат: "), 2, 0 ,Qt::AlignRight);
        layoutGrid->addWidget ( new QLabel("Выход пользователя из чат: "), 3, 0 ,Qt::AlignRight);
        layoutGrid->addWidget ( new QLabel("Звуковой сигнал: "), 4, 0 ,Qt::AlignRight);
        layoutGrid->addWidget ( new QLabel("Переименование пользователя: "), 5, 0 ,Qt::AlignRight);
        layoutGrid->addWidget ( new QLabel("Строка в канал: "), 6, 0 ,Qt::AlignRight);
        layoutGrid->addWidget ( new QLabel("Строка-me(шепот) в канале: "), 7, 0 ,Qt::AlignRight);
        layoutGrid->addWidget ( new QLabel("Изменение топика: "), 8, 0 ,Qt::AlignRight);
        
        for(i = 0; i < 9; i++)
        {
            QCheckBox *warningCheckBox = new QCheckBox();
            layoutGrid->addWidget ( warningCheckBox, i, 1 );
            warningCheckBox->setChecked(toInt(keys[i],tr("window"),1));
            connect(warningCheckBox, SIGNAL(stateChanged(int)), this, SLOT(stateChangedWarning(int)));
            warningCheckBoxs[i] = warningCheckBox;
           
            QPushButton *warningPushButton = new QPushButton("Изменить"); 
            connect(warningPushButton, SIGNAL(clicked()), this, SLOT(colorChange()));
            layoutGrid->addWidget ( warningPushButton, i, 2 );
            warningPushButtons[i] = warningPushButton;

            QPixmap color(24,24);
            color.fill(QColor(toInt(keys[i],tr("color"),0xFFFFFF)));
            QLabel *colorLabel = new QLabel(); 
            colorLabel->setPixmap(color);
            layoutGrid->addWidget ( colorLabel, i, 3 );
            colorLabels[i] = colorLabel;
        }
        
    layout->addItem(layoutGrid); 
    layout->addWidget( new QLabel("<br><b>Звуки:</b>"));

        QGridLayout *layoutSoundGrid = new QGridLayout();
        layoutSoundGrid->setSpacing(3);
     //   layoutSoundGrid->setAlignment(Qt::AlignLeft);
        layoutSoundGrid->addWidget ( new QLabel("Личное сообщение: "), 0, 0 ,Qt::AlignRight);
        layoutSoundGrid->addWidget ( new QLabel("Массовое сообщение: "), 1, 0 ,Qt::AlignRight);
        layoutSoundGrid->addWidget ( new QLabel("Вход пользователя в чат: "), 2, 0 ,Qt::AlignRight);
        layoutSoundGrid->addWidget ( new QLabel("Выход пользователя из чат: "), 3, 0 ,Qt::AlignRight);
        layoutSoundGrid->addWidget ( new QLabel("Звуковой сигнал: "), 4, 0 ,Qt::AlignRight);
        layoutSoundGrid->addWidget ( new QLabel("Переименование пользователя: "), 5, 0 ,Qt::AlignRight);
        layoutSoundGrid->addWidget ( new QLabel("Строка в канал: "), 6, 0 ,Qt::AlignRight);
        layoutSoundGrid->addWidget ( new QLabel("Строка-me(шепот) в канале: "), 7, 0 ,Qt::AlignRight);
        layoutSoundGrid->addWidget ( new QLabel("Изменение топика: "), 8, 0 ,Qt::AlignRight);
        
        for( i = 0; i < 9; i++)
        {
            QCheckBox *warningCheckBox = new QCheckBox();
            layoutSoundGrid->addWidget ( warningCheckBox, i, 1 );
            warningCheckBox->setChecked(toInt(keys[i],tr("sound"),1));
            connect(warningCheckBox, SIGNAL(stateChanged(int)), this, SLOT(stateChangedSoundWarning(int)));
            soundCheckBoxs[i] = warningCheckBox;
            
            QPushButton *soundPushButton = new QPushButton("Изменить"); 
            connect(soundPushButton, SIGNAL(clicked()), this, SLOT(fileSoundChange()));
            layoutSoundGrid->addWidget ( soundPushButton, i, 2 );
            soundPushButtons[i] = soundPushButton;

            QLabel *fileLabel = new QLabel(get(keys[i],tr("sound_file"),tr("/sound/sound.wav"))); 
            layoutSoundGrid->addWidget ( fileLabel, i, 3 );
            fileLabels[i] = fileLabel;
            
        }
    layout->addItem(layoutSoundGrid); 
    layout->addStretch(1);       
    widget->setLayout(layout); 
    return widget; 
};

void dSettingWarning::stateChangedWarning ( int state )
{
    for(int i = 0; i < 9; i++)
    {
        QCheckBox *warningCheckBox =warningCheckBoxs[i];
            if( warningCheckBox->hasFocus() )
                if ( state > 0 )
                    set(keys[i],tr("window"),1);
                else
                    set(keys[i],tr("window"),0);
    }
}

void dSettingWarning::stateChangedSoundWarning ( int state )
{
    for(int i = 0; i < 9; i++)
    {
        QCheckBox *warningCheckBox =soundCheckBoxs[i];
            if( warningCheckBox->hasFocus() )
                if ( state > 0 )
                    set(keys[i],tr("sound"),1);
                else
                    set(keys[i],tr("sound"),0);
    }
}

void dSettingWarning::fileSoundChange()
{

    for(int i = 0; i < 9; i++)
    {
        QPushButton *soundPushButton =soundPushButtons[i];
            if( soundPushButton->hasFocus() )
            {
                QString fileName =
                        QFileDialog::getOpenFileName(0, tr("Открыть звуковой файл."),
                                            QDir::currentPath(),
                                            tr("Wave Files (*.wav)"));
                if (fileName.isEmpty())
                    return;
                
                QDir dir(QCoreApplication::applicationDirPath());
                fileLabels[i]->setText(dir.relativeFilePath(fileName));
                set(keys[i],tr("sound_file"),dir.relativeFilePath(fileName));
            }
    }
}

void dSettingWarning::colorChange()
{

    for(int i = 0; i < 9; i++)
    {
        QPushButton *warningPushButton =warningPushButtons[i];
            if( warningPushButton->hasFocus() )
            {
            
                QColor color = QColorDialog::getColor(QColor(toInt(keys[i],tr("color"),0xFFFFFF)));
                QPixmap pixmap(24,24);
                pixmap.fill(color);
                colorLabels[i]->setPixmap(pixmap);

                set(keys[i],tr("color"),color.rgb());
            }
    }
}
void dSettingWarning::timeChanged(int _value)
{
    windowTimeOut = _value;
    set(tr("time"),tr("value"),_value);
}    

void dSettingWarning::maxWindowChanged(int _value)
{
    maxWindow = _value;
    set(tr("max_window"),tr("value"),_value);
} 