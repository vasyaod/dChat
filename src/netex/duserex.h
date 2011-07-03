//*********************************************************************
//  Файл содержит класс dUserEx, представляющий собой расширение класса 
// dUser. Добовляет возможность интеграции сетевого модуля в графическую
// оболочку. В связи с этим в класс dUser, было добавлено несколько 
// виртуальных методов для расширения интерфейса. Описание класса dUser 
// можно отыскать в файле duser.h
// Корективы были внесены так же в описание dLocalUser и dRemoteUser, у них
// был изменен базовый класс.

#ifndef DUSEREX_H
#define DUSEREX_H

#include <QtGui>
#include "../net/duser.h"

class dChatApplication;

class dUserEx : public dUser
{
//    Q_OBJECT
    private:
        dChatApplication *application;
    // Добавляет новый пункт в список(в QListWidget), приэтом создает 
    // визуальное оформление.
        void addItemToList();
    // Указатель на модель данных (таблицу).
        QAbstractItemModel *model;
    // Осуществляет поиск этого объекта в базе данных( в модели ).
        QModelIndex find_index();
    // Изменяет ToolTip для конкретного пользователя в пункте.
        void set_tool_tip( QModelIndex index );
    protected:
    // Перегружим некоторые виртуальные функции, дабы изменить интерфейс
    // при их вызове.

		virtual void set_avatar(const QPixmap &_avatar);
		virtual bool set_name(const QString &_name);
		virtual void set_host(const QString & _host);
		virtual void set_login(const QString &_login);
		virtual void set_version(const QString &_version);
        virtual void set_auto_answer(const QString & _auto_answer);
		virtual void set_sex(const uint &_sex);
		virtual void set_mode(const uint &_mode);
		virtual void set_activity(const bool &_activity);
		virtual void set_xml_protocol(uint _xml_protocol);   

    // ПЕРЕГРУЗКА СОБЫТИЙ...
//        virtual void event_msg_image( dUser *_from ){};        

    public:
		dUserEx( dManager * _manager, const QHostAddress &_ip, const QString &_name);
        virtual ~dUserEx();
            
};

#endif	//DUSEREX_H
