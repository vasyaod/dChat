/****************************************************************************
** Meta object code from reading C++ file 'dtrayicon.h'
**
** Created: ?? 14. ??? 14:20:53 2005
**      by: The Qt Meta Object Compiler version 58 (Qt 4.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dtrayicon.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dtrayicon.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 58
#error "This file was generated using the moc from 4.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dTrayIcon[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      28,   10,   10,   10, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_dTrayIcon[] = {
    "dTrayIcon\0\0leftButtonDown()\0rightButtonDown()\0"
};

const QMetaObject dTrayIcon::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_dTrayIcon,
      qt_meta_data_dTrayIcon, 0 }
};

const QMetaObject *dTrayIcon::metaObject() const
{
    return &staticMetaObject;
}

void *dTrayIcon::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dTrayIcon))
	return static_cast<void*>(const_cast<dTrayIcon*>(this));
    if (!strcmp(_clname, "dTrayIcon/1.0"))
	return static_cast<dTrayIcon*>(const_cast<dTrayIcon*>(this));
    return QObject::qt_metacast(_clname);
}

int dTrayIcon::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: leftButtonDown(); break;
        case 1: rightButtonDown(); break;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void dTrayIcon::leftButtonDown()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
};

// SIGNAL 1
void dTrayIcon::rightButtonDown()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
};
