#ifndef DSETTINGLOCALUSER_H
#define DSETTINGLOCALUSER_H

#include <QtGui>
#include <QtXml>
#include "../dsetting.h"

class dLocalUser;

class dSettingLocalUser: public dSetting
{
    Q_OBJECT
    private:
    // Строка правки имени.
        QLineEdit *nameLineEdit;
    // Редактор авто ответа.
        QTextEdit * auto_answerEdit;
    // Строка правки логина.
        QLineEdit * loginLineEdit;
    // Лабел с аватаром
        QLabel *avatarLabel;
    // Кнопка изменеия авто-ответа.
        QPushButton *avatarPushButton;
    // См. ниже.
        dLocalUser *user;
    // Комбо с настройками пола.
        QComboBox *sexComboBox;
    // CheckBox с настройкой поссивного режима.
        QCheckBox *passiveModeCheckBox;
//        dChatApplication *application;    
    public:
    
        dSettingLocalUser( QDomElement &_parentXmlElement, dSetting *_parent, dLocalUser *_usr);
//        ~dSettingUsers();
        virtual QWidget *createWidget();
    
    // Возвращмет true если пользователь находиться в пассивном режиме.
        bool hasPassiveMode(){ return toInt(tr("passive_mode"),tr("value"),0); };
    
    public slots:
    // При нажатии кнопки выбора аватара.
        void clickedAvatarButton ( bool checked );
    // При смене имени.        
        void nameEdited();
    // При смене логина.        
        void loginEdited( const QString& _login);
    // При смене авто-ответа
        void autoAnswerChanged();
    // При смене пола.
        void sexActivated ( int index );
    // При смене режима пользоателя.
        void passiveModeChanged( int _state);
    
};

#endif // DSETTINGLOCALUSER_H

