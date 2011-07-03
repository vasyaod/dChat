//*********************************************************************
//  Файл содержит класс dManagerEx, представляющий собой расширение класса 
// dManager. Добовляет возможность интеграции сетевого модуля в графическую
// оболочку. В связи с этим в класс dManager, было добавлено несколько 
// виртуальных методов для расширения интерфейса. Описание класса dManager 
// можно отыскать в файле dmanager.h
//  В часности была организована предача указателя на объект "приложения",
// в дальнейшем это позволит обратиться к любому окну(widget-у) в программе.

#ifndef DMANAGEREX_H
#define DMANAGEREX_H

#include <QtGui>

#include "../net/dmanager.h"

class dManagerEx : public dManager
{
    // Обьявим друзей класса.
	friend dUser::~dUser();
    friend dUser::dUser( dManager * _manager, 
                         const QHostAddress &_ip, 
                         const QString &_name );

    Q_OBJECT
    private:
        QStandardItemModel *model;
        QItemSelectionModel *selectionModel;

     //   dChatApplication * application;
    
    protected:
    // Методы добавляют(удаляют) пользователя в список(из списка).
    // Перезагрузим в связи с небольшими добавлениями.
		virtual dUser *addUser(dUser * usr);
		virtual void deleteUser(dUser * usr);
    
    public:
    // КОНСТРУКТОР И ДЕСТРУКТОР.
        dManagerEx( dChatApplication * _application );
        ~dManagerEx();

    // Возвращает пользователя который является текущим в модели.
        dPUser getCurrentUserToModel(/* QModelIndex &_index */);

    // Возвращает список пользователей которые выделены в модели.
        QList<dPUser> getSelectedUserToModel();
        		    
    // Возвращает указатель на модель данных и на 
    // модель выделения данных    
        virtual QStandardItemModel *get_model() const{ return model; };
        virtual QItemSelectionModel *get_selectionModel() const{ return selectionModel; };
        
    ///////////////////// Перегружаем события. /////////////////////    
    // Перегружаем события из dManager, чтобы иметь возможность 
    // послать сигналы.
    // Событие происходит при смене активности.
		virtual void event_change_activity( dPUser _from )
                { emit signal_change_activity(_from); };
    // Событие происходит при смене режима.
		virtual void event_change_mode( dPUser _from )
                { emit signal_change_mode(_from); };
    // Событие происходит, при входе какого либо пользователя в чат.
		virtual void event_msg_enter( dPUser _from )
                { emit signal_msg_enter(_from); };
    // Событие происходит, при выходе пользователя из чата.
		virtual void event_msg_exit( dPUser _from )
                { emit signal_msg_exit(_from); };
    // Событие происходит, при выходе пользователя из чата.
		virtual void event_msg_rename( dPUser _from, const QString & _oldname )
                { emit signal_msg_rename(_from,_oldname); };
    // Событие происходит, когда приходит личное сообщение.
		virtual void event_msg_personal( dPUser _from, dPUser _to ,const QString & _msg, bool _html = false)
                { emit signal_msg_personal(_from,_to,_msg,_html); };
    // Событие происходит, когда приходит сообщение в канал.
		virtual void event_msg_channel( dPUser _from, const QString & _msg)
                { emit signal_msg_channel(_from,_msg); };
    // Событие происходит, когда приходит звуковой сигнал.
		virtual void event_msg_beep( dPUser _from, dPUser _to )
                { emit signal_msg_beep(_from,_to); };
    // Событие происходит, при получении массового сообщения.
		virtual void event_msg_mass( dPUser _from, dPUser _to, const QString & _msg, bool _html = false )
                {  emit signal_msg_mass(_from,_to,_msg,_html);  };
    // Событие происходит, при смене топика.
		virtual void event_change_topic( const QString &_topic )
                { emit signal_change_topic(_topic); };
    // Событие происходит, когда приходит сообщение с текущим топиком.
		virtual void event_current_topic( const QString &_topic)
                { emit signal_current_topic(_topic); };
    // Событие происходит, когда приходит сообщение в канал с пометкой 
    // шепнуть (Me-сообщения).event_change_topic
		virtual void event_msg_channel_me( dPUser _from, const QString &_msg)
                { emit signal_msg_channel_me(_from,_msg); };
    // Событие происходит, при получении авто-ответа.
		virtual void event_msg_auto_answer( dPUser _from, dPUser _to, const QString & _msg)
                { emit signal_msg_auto_answer(_from,_to,_msg); };
    // Событие происходит ,когда приходит Xml - сообщение.
		virtual void event_xml( dPUser _from, dPUser _to, const QString & _msg)
                { emit signal_xml(_from,_to,_msg); };
        
    public slots:
    // Слот, вызывается при смене выделенного пункта в списке пользователей.
    // Функция должна поменять цвета виджета, этих пунктов.
    // void userListItemChanged( QListWidgetItem * current, QListWidgetItem * previous);
    
    signals:
    // Сигнал, подается при изменении количества пользователей.
    // в момент создания нового пользователя.
        void signal_count_user_change( int _count );    
        
    // Сигналы, которые посылаются соответствующими событьями.
    // Смотр. выше.............
		void signal_change_activity( dPUser _from );
		void signal_change_mode( dPUser _from );
		void signal_msg_enter( dPUser _from );
		void signal_msg_exit( dPUser _from );
		void signal_msg_rename( dPUser _from, const QString & _oldname );
		void signal_msg_personal( dPUser _from, dPUser _to ,const QString & _msg, bool _html = false);
		void signal_msg_channel( dPUser _from, const QString & _msg);
		void signal_msg_beep( dPUser _from, dPUser _to );
		void signal_msg_mass( dPUser _from, dPUser _to ,const QString & _msg, bool _html = false);
		void signal_change_topic( const QString &_topic );
		void signal_current_topic( const QString &_topic);
		void signal_msg_channel_me( dPUser _from, const QString &_msg);
		void signal_msg_auto_answer( dPUser _from, dPUser _to, const QString & _msg);
		void signal_xml( dPUser _from, dPUser _to, const QString & _msg);
    
    // Сигналы посылается при добавлении и удалении пльзователя.
        void signal_delete_user( dPUser _user );
        void signal_add_user( dPUser _user );

};
#endif	//DMANAGEREX_H
