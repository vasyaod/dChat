/****************************************************************************
** Meta object code from reading C++ file 'dservice.h'
**
** Created: ?? 8. ??? 04:12:17 2005
**      by: The Qt Meta Object Compiler version 58 (Qt 4.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dservice.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dservice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 58
#error "This file was generated using the moc from 4.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dService[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      25,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_dService[] = {
    "dService\0\0dataReceived()\0dataReceivedPath()\0"
};

const QMetaObject dService::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_dService,
      qt_meta_data_dService, 0 }
};

const QMetaObject *dService::metaObject() const
{
    return &staticMetaObject;
}

void *dService::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dService))
	return static_cast<void*>(const_cast<dService*>(this));
    return QObject::qt_metacast(_clname);
}

int dService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: dataReceived(); break;
        case 1: dataReceivedPath(); break;
        }
        _id -= 2;
    }
    return _id;
}
