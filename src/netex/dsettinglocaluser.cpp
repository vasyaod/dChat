#include "dlocaluserex.h"
#include "dmanagerex.h"
#include "dsettinglocaluser.h"

#include "../dchatapplication.h"
#include "../duserwindow.h"

dSettingLocalUser::dSettingLocalUser( QDomElement &_parentXmlElement, dSetting *_parent, dLocalUser *_usr):
            dSetting(_usr->get_type(),_parentXmlElement,_parent ),
            user(_usr)
{
    QString avatarPath = get(tr("avatar"),tr("value"),tr("avatar/noavatar.png"));
    user->set_avatar(QPixmap(avatarPath));
    user->set_login(get(tr("login"),tr("value"),tr("Entry in system not executed. :)")));
	user->set_auto_answer(get(tr("auto_answer"),tr("value"),tr("")));
	user->set_sex(toInt(tr("sex"),tr("value"),0));
    
    setIcon(QIcon(user->get_avatar()));
    setTitle(user->get_name()+tr(" (%1)").arg(user->get_type()));
};

QWidget *dSettingLocalUser::createWidget()
{ 
    QWidget * widget =  new QWidget();
    QVBoxLayout *layout_main = new QVBoxLayout;
            
        QGridLayout *layout = new QGridLayout();
        layout->setAlignment(Qt::AlignRight);
        layout->addWidget ( new QLabel(tr("Имя:")), 1, 0 ,Qt::AlignRight);
        layout->addWidget ( new QLabel(tr("Авто-ответ:")), 2, 0,Qt::AlignTop );
        layout->addWidget ( new QLabel(tr("Логин:")), 3, 0 ,Qt::AlignRight);
        layout->addWidget ( new QLabel(tr("Пол:")), 4, 0 ,Qt::AlignRight);
    //    layout->addWidget ( new QLabel("Аватар:"), 3, 0 );
        
        nameLineEdit = new QLineEdit(user->get_name());
        connect(nameLineEdit, SIGNAL(editingFinished()), this, SLOT(nameEdited()));
        layout->addWidget ( nameLineEdit, 1, 1 );

        auto_answerEdit = new QTextEdit();
        auto_answerEdit->setPlainText(user->get_auto_answer());
        connect(auto_answerEdit, SIGNAL(textChanged()), this, SLOT(autoAnswerChanged()));
        layout->addWidget ( auto_answerEdit, 2, 1 );

        loginLineEdit = new QLineEdit(user->get_login());
        connect(loginLineEdit, SIGNAL(textEdited(const QString&)), this, SLOT(loginEdited(const QString&)));
        layout->addWidget ( loginLineEdit, 3, 1 );

        QHBoxLayout *sexLayout = new QHBoxLayout;
        sexLayout->setSpacing(15);
            sexComboBox = new QComboBox;
            sexComboBox->addItem(tr("Безполый"));
            sexComboBox->addItem(tr("Женский"));
            sexComboBox->addItem(tr("Мужской"));
            sexComboBox->setCurrentIndex(user->get_sex());
            connect(sexComboBox, SIGNAL(activated (int)), this, SLOT(sexActivated (int)));
            sexLayout->addWidget (sexComboBox );
            sexLayout->addStretch ( 1 );            
        layout->addLayout( sexLayout, 4, 1 );

        avatarPushButton = new QPushButton(tr("Изменить аватар"));
        avatarPushButton->setDefault(true);
        avatarPushButton->setIcon(QIcon(tr("pic/open32x32.png")));
        connect(avatarPushButton, SIGNAL(clicked(bool)), this, SLOT(clickedAvatarButton(bool)));
        layout->addWidget ( avatarPushButton, 0, 1 );
        avatarLabel = new QLabel();
        QPixmap avatar = user->get_avatar();
        avatar.scaled(48,48);
        avatarLabel->setPixmap(avatar);
        layout->addWidget ( avatarLabel , 0, 0 );

    layout_main->addLayout( layout );
    
    QCheckBox *passiveModeCheckBox = new QCheckBox(tr("Пассивный режим"));
    passiveModeCheckBox->setChecked(toInt(tr("passive_mode"),tr("value"),0));
    connect(passiveModeCheckBox, SIGNAL(stateChanged(int)), this, SLOT(passiveModeChanged(int)));
    
    layout_main->addWidget ( passiveModeCheckBox );
    layout_main->addWidget ( new QLabel(tr("При использовании пассивного режима пользователя не видят в других чатах!")) );
    widget->setLayout(layout_main);     
    return widget; 
};

void dSettingLocalUser::passiveModeChanged( int _state )
{
    set(tr("passive_mode"),tr("value"), !_state ? 0 : 1); 
}

void dSettingLocalUser::clickedAvatarButton ( bool checked )
{
    QString fileName =
            QFileDialog::getOpenFileName(0, tr("Загрузить скин"),
                                         QDir::currentPath(),
                                         tr("Images (*.bmp *.png)"));
    if (fileName.isEmpty())
        return;
        
    QDir dir(QCoreApplication::applicationDirPath());
    user->set_avatar(QPixmap(dir.relativeFilePath(fileName))); 
    setIcon(QIcon(dir.relativeFilePath(fileName))); 
    avatarLabel->setPixmap(user->get_avatar());
    set(tr("avatar"),tr("value"),dir.relativeFilePath(fileName));
    saveSetting();
    reParsing();   
  //  saveSetting();   
}
void dSettingLocalUser::nameEdited( )
{
    QString _name = nameLineEdit->text();
    if( _name != user->get_name() )
    {
        if( !user->get_manager()->find_user(user->get_ip(),_name) )
        {
            getParentXmlElement().setAttribute(tr("name"),_name);
            user->set_name(_name);
            setTitle(_name+tr(" (%1)").arg(user->get_type()));
            saveSetting();
            reParsing();
        }
        else
            QMessageBox::warning (0, tr("Замечание."),
                                     tr("Пользователь с именем %1 уже существует.").arg(_name),QMessageBox::Ok,0,0);        

    }
};

void dSettingLocalUser::loginEdited( const QString& _login)
{
    user->set_login(_login);
    set(tr("login"),tr("value"),_login);
};

void dSettingLocalUser::autoAnswerChanged()
{
    user->set_auto_answer(auto_answerEdit->toPlainText());
    set(tr("auto_answer"),tr("value"),auto_answerEdit->toPlainText());
}

void dSettingLocalUser::sexActivated ( int index )
{
    set(tr("sex"),tr("value"),sexComboBox->currentIndex());
    user->set_sex(sexComboBox->currentIndex());
}
