#ifndef DPROPERTYWINDOW_H
#define DPROPERTYWINDOW_H

#include <QtGui>
#include "dsetting.h"

class dPropertyWindow : public QMainWindow
{   
    Q_OBJECT
    private:
    
        QHash<dSetting* ,QTreeWidgetItem *> itemForSetting;
        
        dSetting *setting;
        dSetting *curentSelectedSetting;
        void parseSetting( dSetting *_seting, QTreeWidgetItem *parentItem = 0);
    
    // Виджет со деревом параметров.
        QTreeWidget * contentsTree;
    // Виджет со списком окон для настроек.
        QScrollArea * propertyList;
        QWidget * propertyList_second;

    // Окно с деревом настроек.
        QDockWidget * contentsWidget;
    protected:
        virtual void hideEvent ( QHideEvent * event );
        
    public:
        dPropertyWindow(dSetting *_seting ,QWidget * _parent = 0, Qt::WFlags _flags = 0);
        ~dPropertyWindow();
    // Вот такой вот, каламбур.....
        void setSeting(dSetting *_setting){ setting = _setting; };
        dSetting *getSeting(){ return setting; };
        
        
    public slots:
        void openSetting();
        void saveSetting();
        void closeSideWindow( bool _checked );

    // Метод создан чтобы сазу переходить на нужную настройку.
    // и показать имено её.
        void goSetting( dSetting *_setting );

    // Вызывается когда надо перестроить дерево настроек.
        void reParsing();    

    protected slots:
        void itemChanged( QTreeWidgetItem * current, QTreeWidgetItem * previous  );
    
};

#endif // DPROPERTYWINDOW_H
