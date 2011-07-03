#ifndef DLOCALUSEREX_H
#define DLOCALUSEREX_H

#include <QtGui>

#include "../net/dlocaluser.h"

class dSettingLocalUser;
class dSetting;
class dChatApplication;
class dManagerEx;

class dLocalUserEx: public dLocalUser
{
    Q_OBJECT
    private:
    // Настройки этого пользователя.
        QAction *userMenuAct;
        QString user_type;
    protected:
        dSettingLocalUser *setting;     // Основные настройки пользователя.
        dChatApplication *application;  // Указатель на класс приложения.

    // Перегружены из-за возможноси создания пассивного режима
    // ПЕРЕГРУЖАЕМ Эхо-запрос.
		virtual void event_echo_request( dPUser _from );
    // ПЕРЕГРУЖАЕМ Info-запрос.
		virtual void event_info_request( dPUser _from );
        
	public:
		dLocalUserEx(   dManagerEx * _manager, 
                        const QString &_name,
                        const QString &_user_type, 
                        QDomElement &_parentXmlElement, 
                        dSetting *_parentSetting = 0);
		~dLocalUserEx();

    // Методы устанавливают и возвращают тип пользователя.
        virtual QString get_type() const{ return user_type; };
        virtual void set_type(QString &_user_type) { user_type = _user_type; };
    // Перегрузим метод установки главного пользователя.
        virtual bool set_main_user();
    // Перегрузим некоторые методы установки свойств пользователя.
		virtual bool set_name(const QString &_name);
		virtual void set_avatar(const QPixmap &_avatar);
    
    public slots:
    // Вызывается при смене гл. пользователя из меню.
        void setMainUserTriggered( bool _checked );
};
#endif	//DLOCALUSEREX_H
