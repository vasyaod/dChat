#ifndef DSETTINGUSERWIN_H
#define DSETTINGUSERWIN_H

#include <QtGui>
#include <QtXml>
#include "dsetting.h"

class dUserWindow;

class dSettingUserWin: public dSetting
{
    Q_OBJECT
    private:
        dUserWindow *userWindow;
    // Сомбо с размером значков в режиме Зачки.
        QComboBox *iconSizeToIconComboBox;
    // Сомбо с размером значков в режиме Зачки.
        QComboBox *iconSizeToListComboBox;
    // Сомбо с размером значков в режиме Зачки.
        QComboBox *iconSizeToTableComboBox;
        
    // Размеры значков.
        QSize iconSizeToIcon;
        QSize iconSizeToList;
        QSize iconSizeToTable;
        
    public:
        QSize getIconSizeToIcon() const { return iconSizeToIcon; };
        QSize getIconSizeToList() const { return iconSizeToList; };
        QSize getIconSizeToTable() const { return iconSizeToTable; };
    
        dSettingUserWin( const QString &_key, dSetting *_parent, dUserWindow *_userWindow );
        ~dSettingUserWin();

        virtual QWidget *createWidget();
    
    public slots:
    // Слот, выполняется при изменении размеров соответствующих иконок.
        void sizeIconToIconActivated( int _index );
        void sizeIconToListActivated( int _index );
        void sizeIconToTableActivated( int _index );
};

#endif // DSETTINGUSERWIN_H

