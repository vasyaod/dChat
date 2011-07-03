#ifndef DSETTINGNET_H
#define DSETTINGNET_H

#include <QtGui>
#include <QtXml>
#include "../dsetting.h"

class dChatApplication;
class dService;
class dAbstractIPListEx;

class dSettingNet: public dSetting
{
    Q_OBJECT
    private:
        dChatApplication *application;
    // Виджет содержит номер порта.
        QSpinBox *portSpinBox;
    // Виджет содержит время жизни не активного пользователя в списке.
        QSpinBox *timeoutSpinBox;
    // Виджет содержит интервал посылания массовых эхо-запросов.
        QSpinBox *refreshSpinBox;
    // Виджет содержит интервал обновления информации о пользователе.
        QSpinBox *refreshInfoSpinBox;
    // Виджет содержит широковещательный адрес.
        QLineEdit *broadcastIPLineEdit;  
    // Указатель на сервис чата.
        dService * dchat;     
    // Список IP адресов рассылки.
        QList<dAbstractIPListEx*> ip_lists;
    // Виджет со списком.
        QListWidget*ipList;
    // Спроки с адресами.
        QLineEdit *IP1LineEdit;
        QLineEdit *IP2LineEdit;
        QLineEdit *IP3LineEdit;
    // Окно редактирования диапазона.
        QWidget * rangeIPWindow;
    // Окно редактирования диапазона.
        QWidget * singleIPWindow;
    // Виджет с выбором сетевой библиотеки.
        QComboBox *networkModuleComboBox;
    public:
   
        dSettingNet( dSetting *_parent );
        ~dSettingNet();

        virtual QWidget *createWidget();
    
    public slots:
    // При нажатии кнопки "применить".
        void clickedUseButton( bool _checked );  
    // При смене интервалов.
        void timeoutChanged( int _value );
        void refreshChanged( int _value );
        void refreshInfoChanged( int _value );
    // При нажатии клавиши добавления диапазона адресов.
        void clickedAddRangeIPWindowButton();
        void clickedAddRangeIPButton();
    // При нажатии клавиши добавления адреса.
        void clickedAddSingleIPWindowButton();
        void clickedAddSingleIPButton();
    // При нажатии клавиши удаления адреса.
        void clickedDeleteIPButton();
    // При выборе текущего типа отправкии масовых сообщений.
        void sendTypeActivated( int _index );
};

#endif // DSETTINGNET_H

