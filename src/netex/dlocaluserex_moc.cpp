/****************************************************************************
** Meta object code from reading C++ file 'dlocaluserex.h'
**
** Created: ?? 12. ??? 09:44:25 2006
**      by: The Qt Meta Object Compiler version 58 (Qt 4.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dlocaluserex.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dlocaluserex.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 58
#error "This file was generated using the moc from 4.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dLocalUserEx[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      23,   14,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dLocalUserEx[] = {
    "dLocalUserEx\0\0_checked\0setMainUserTriggered(bool)\0"
};

const QMetaObject dLocalUserEx::staticMetaObject = {
    { &dLocalUser::staticMetaObject, qt_meta_stringdata_dLocalUserEx,
      qt_meta_data_dLocalUserEx, 0 }
};

const QMetaObject *dLocalUserEx::metaObject() const
{
    return &staticMetaObject;
}

void *dLocalUserEx::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dLocalUserEx))
	return static_cast<void*>(const_cast<dLocalUserEx*>(this));
    return dLocalUser::qt_metacast(_clname);
}

int dLocalUserEx::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = dLocalUser::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setMainUserTriggered(*(bool*)_a[1]); break;
        }
        _id -= 1;
    }
    return _id;
}
