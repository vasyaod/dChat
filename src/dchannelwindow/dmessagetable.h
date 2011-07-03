#ifndef DMESSAGETABLE_H
#define DMESSAGETABLE_H

#include <QtGui>
#include "../net/duser.h"

class dChatApplication;

class dMessageItemWidget : public QStackedWidget
{
    private:
        QLabel *labelWidget;
        QTextEdit *editWidget;
            
    public:
        dPUser from;
        QString name;   
             
        dMessageItemWidget( const QString &_msg, QWidget * _parent = 0 );
        virtual QSize sizeHint () const;
    protected:
        virtual void mousePressEvent ( QMouseEvent * _event );
    //    virtual void keyPressEvent ( QKeyEvent * _event );
};

class dTextEditMessageEx : public QTextEdit
{
    private:
        dChatApplication *application; 
        dMessageItemWidget * messageItemWidget;   
    public:
        dTextEditMessageEx( dMessageItemWidget * _messageItemWidget ):messageItemWidget(_messageItemWidget),QTextEdit(_messageItemWidget){};
    protected:
        bool event ( QEvent * _event );
};

//******************************************************************
//                          dMessageTable
//******************************************************************
class dMessageTable : public QTableWidget
{
    Q_OBJECT
    private:
        dChatApplication *application;
        int scrollTimerID;

    // ƒействи€, созданы дл€ контекстного меню.
        QAction *sendMessageAct;
        QAction *sendBeepAct;
        QAction *userInfoAct;
        QAction *findToListAct;
        QAction *clearAct;
        
    // ћаксимальное количество строк в таблице.
        uint maxString;
    // ћаксимальное количество симвалов в имени пользовател€.
        uint maxName;
    // ћетод возвращает пользовател€ на которого указывает текущаа строка таблицы.
        dPUser getUserInTable();

    public:
        dMessageTable( QWidget * _parent = 0 );

    // ƒобавл€ет сообщение из канала.
        void addMessage( dPUser _from, const QString &_mgs);
    // ¬озвращает максимальное количаство строк в таблице.
    //    uint getMaximumString(){ return maxString; };
    // ”станавливает максимальное количаство строк в таблице.
        void setMaximumName( uint _maxName ){ maxName=_maxName; };
    // ”станавливает максимальное количаство строк в таблице.
        void setMaximumMessage( uint _maxString ){ maxString=_maxString; };

    protected:
        virtual void timerEvent ( QTimerEvent * _event );        
    // ѕри ресайзе нужно помен€ть размер колонки.
        virtual void resizeEvent ( QResizeEvent * _event );
    
    public slots:
    // ¬ызываетс€ при клике мыши на заголовке.
        void sectionClicked( int logicalIndex );
    //  огда нужно очистить канал
        void clearToggled( bool _clickable );
    // ≈сли нужно найти пользовател€ в списке.
        void findToListToggled( bool _clickable );
    // ≈сли нужно найти послать сообщение пользователю.
        void sendMessageToggled( bool _clickable );
    // «вуковой вызов....
        void sendBeepToggled( bool _clickable );

    signals:
    // —игнал подаетс€ если нужно воткнуть им€ пользовател€ в строку редактировани€
    // сообщени€.
        void addNameSignal( const QString &_name );
};

#endif // DMESSAGETABLE_H

