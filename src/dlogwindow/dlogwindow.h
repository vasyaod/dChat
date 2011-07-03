#ifndef DLOGWINDOW_H
#define DLOGWINDOW_H

#include <QtGui>
#include <QtXml>

#include "../net/duser.h"

class dChatApplication;
class dSetting;

class dLogWindow : public QMainWindow
{   
    Q_OBJECT
    private:
        dChatApplication *application;
    // Окно с деревом настроек.
        QDockWidget * contentsWidget;
        QStackedWidget *centralWidget;
    // Окно с системными сообщениями.
        QTextEdit *systemMessageEditor;
    // Таблица с массовыми сообщениями.
        QTableWidget *massMessageTable;
    // Таблица с логом сообщений.
        QTableWidget *messageLogTable;
    // Переделывает некоторые символы, которые нельзя использовать в XML.
        QString escapeXml(QString xml);
    // Настройки окна с логами.
        dSetting *settingLogWindow;
    // Галочка - "Убрать повторяющиеся".
        QCheckBox *doubleCheckBox;
    // XML-ный документ с логами сообщений.
        QDomDocument logDocument; 
    // Добавляет строку в таблицу лога сообщений...
        void addLogTable(   const QString & _date_time,
                            const QString & _fromName,
                            const QString & _fromIp,
                            const QString & _toName,
                            const QString & _toIp,
                            const QString & _msg,
                            bool _html = false );   
    public:
        dLogWindow( QWidget * _parent = 0, Qt::WFlags _flags = 0 );
        ~dLogWindow();
    
    public slots:
    // При двойном клике в таблице сообщений.
        void tableDoubleClicked ( QTableWidgetItem * item );
    // При нажатии кнопки закрытия панели логов.
        void closeSideWindow( bool _checked );
    // При измении пункта меню
        void itemChanged ( int _index );
    // Срабатывает при изменении галочки "Убрать повторяющиеся".
        void doubleMassStateChanged ( int _state );
    // Вызывается при нажатии клавиши очистки лога.
        void clearLog();
    // Слоты вызываются при получении одноименных сообщений. cм dUser и dManagerEx.        
        void slot_msg_channel( dPUser _from, const QString & _msg );
        void slot_msg_channel_me( dPUser _from, const QString & _msg );
        void slot_change_topic( const QString & _topic );
        void slot_msg_enter( dPUser _from );
        void slot_msg_exit( dPUser _from );
        void slot_msg_beep( dPUser _from, dPUser _to);
        void slot_msg_personal( dPUser _from, dPUser _to , const QString & _msg, bool _html);
        void slot_msg_mass( dPUser _from, dPUser _to, const QString & _msg, bool _html);
        void slot_msg_rename( dPUser _from, const QString &_oldname);
        void slot_msg_auto_answer( dPUser _from, dPUser _to, const QString & _msg);
};

#endif // DLOGWINDOW_H
