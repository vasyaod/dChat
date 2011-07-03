/****************************************************************************
** Meta object code from reading C++ file 'duserwindow.h'
**
** Created: ?? 7. ??? 21:57:49 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "duserwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'duserwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dUserWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      34,   12,   12,   12, 0x0a,
      43,   12,   12,   12, 0x0a,
      55,   12,   12,   12, 0x0a,
      70,   62,   12,   12, 0x0a,
      91,   62,   12,   12, 0x0a,
     113,   62,   12,   12, 0x0a,
     135,   62,   12,   12, 0x0a,
     158,   62,   12,   12, 0x0a,
     181,   12,   12,   12, 0x2a,
     200,   62,   12,   12, 0x0a,
     227,   12,   12,   12, 0x2a,
     250,   62,   12,   12, 0x0a,
     274,   12,   12,   12, 0x2a,
     294,   62,   12,   12, 0x0a,
     318,   12,   12,   12, 0x2a,
     338,   62,   12,   12, 0x0a,
     365,   12,   12,   12, 0x2a,
     388,   62,   12,   12, 0x0a,
     412,   12,   12,   12, 0x2a,
     432,   62,   12,   12, 0x0a,
     464,   12,   12,   12, 0x2a,
     496,  492,   12,   12, 0x0a,
     531,   12,   12,   12, 0x0a,
     565,  558,   12,   12, 0x0a,
     596,  586,   12,   12, 0x0a,
     648,  619,   12,   12, 0x0a,
     685,  679,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dUserWindow[] = {
    "dUserWindow\0\0searchWidgetUpdate()\0closed()\0minimized()\0show()\0"
    "checked\0viewBarToggled(bool)\0viewIconToggled(bool)\0"
    "viewListToggled(bool)\0viewTableToggled(bool)\0refreshTriggered(bool)\0"
    "refreshTriggered()\0refreshInfoTriggered(bool)\0refreshInfoTriggered()\0"
    "userInfoTriggered(bool)\0userInfoTriggered()\0sendBeepTriggered(bool)\0"
    "sendBeepTriggered()\0sendMessageTriggered(bool)\0sendMessageTriggered()\0"
    "sendMassTriggered(bool)\0sendMassTriggered()\0"
    "sendPersonalMassTriggered(bool)\0sendPersonalMassTriggered()\0pos\0"
    "customContextMenuRequested(QPoint)\0searchTextChanged(QString)\0_count\0"
    "countUserChange(int)\0pos,index\0splitterMoved(int,int)\0"
    "logicalIndex,oldSize,newSize\0tableHeaderResize(int,int,int)\0index\0"
    "itemDoubleClicked(QModelIndex)\0"
};

const QMetaObject dUserWindow::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_dUserWindow,
      qt_meta_data_dUserWindow, 0 }
};

const QMetaObject *dUserWindow::metaObject() const
{
    return &staticMetaObject;
}

void *dUserWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dUserWindow))
	return static_cast<void*>(const_cast<dUserWindow*>(this));
    return QObject::qt_metacast(_clname);
}

int dUserWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: searchWidgetUpdate(); break;
        case 1: closed(); break;
        case 2: minimized(); break;
        case 3: show(); break;
        case 4: viewBarToggled(*reinterpret_cast< bool*>(_a[1])); break;
        case 5: viewIconToggled(*reinterpret_cast< bool*>(_a[1])); break;
        case 6: viewListToggled(*reinterpret_cast< bool*>(_a[1])); break;
        case 7: viewTableToggled(*reinterpret_cast< bool*>(_a[1])); break;
        case 8: refreshTriggered(*reinterpret_cast< bool*>(_a[1])); break;
        case 9: refreshTriggered(); break;
        case 10: refreshInfoTriggered(*reinterpret_cast< bool*>(_a[1])); break;
        case 11: refreshInfoTriggered(); break;
        case 12: userInfoTriggered(*reinterpret_cast< bool*>(_a[1])); break;
        case 13: userInfoTriggered(); break;
        case 14: sendBeepTriggered(*reinterpret_cast< bool*>(_a[1])); break;
        case 15: sendBeepTriggered(); break;
        case 16: sendMessageTriggered(*reinterpret_cast< bool*>(_a[1])); break;
        case 17: sendMessageTriggered(); break;
        case 18: sendMassTriggered(*reinterpret_cast< bool*>(_a[1])); break;
        case 19: sendMassTriggered(); break;
        case 20: sendPersonalMassTriggered(*reinterpret_cast< bool*>(_a[1])); break;
        case 21: sendPersonalMassTriggered(); break;
        case 22: customContextMenuRequested(*reinterpret_cast< QPoint*>(_a[1])); break;
        case 23: searchTextChanged(*reinterpret_cast< QString*>(_a[1])); break;
        case 24: countUserChange(*reinterpret_cast< int*>(_a[1])); break;
        case 25: splitterMoved(*reinterpret_cast< int*>(_a[1]),*reinterpret_cast< int*>(_a[2])); break;
        case 26: tableHeaderResize(*reinterpret_cast< int*>(_a[1]),*reinterpret_cast< int*>(_a[2]),*reinterpret_cast< int*>(_a[3])); break;
        case 27: itemDoubleClicked(*reinterpret_cast< QModelIndex*>(_a[1])); break;
        }
        _id -= 28;
    }
    return _id;
}
