/****************************************************************************
** Meta object code from reading C++ file 'dsettingusers.h'
**
** Created: ?? 13. ??? 14:33:20 2006
**      by: The Qt Meta Object Compiler version 58 (Qt 4.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dsettingusers.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dsettingusers.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 58
#error "This file was generated using the moc from 4.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dSettingUsers[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      23,   15,   14,   14, 0x0a,
      46,   15,   14,   14, 0x0a,
      78,   72,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dSettingUsers[] = {
    "dSettingUsers\0\0checked\0clickedAddButton(bool)\0"
    "clickedDeleteButton(bool)\0index\0userDoubleClicked(QModelIndex)\0"
};

const QMetaObject dSettingUsers::staticMetaObject = {
    { &dSetting::staticMetaObject, qt_meta_stringdata_dSettingUsers,
      qt_meta_data_dSettingUsers, 0 }
};

const QMetaObject *dSettingUsers::metaObject() const
{
    return &staticMetaObject;
}

void *dSettingUsers::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dSettingUsers))
	return static_cast<void*>(const_cast<dSettingUsers*>(this));
    return dSetting::qt_metacast(_clname);
}

int dSettingUsers::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = dSetting::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clickedAddButton(*(bool*)_a[1]); break;
        case 1: clickedDeleteButton(*(bool*)_a[1]); break;
        case 2: userDoubleClicked(*(QModelIndex*)_a[1]); break;
        }
        _id -= 3;
    }
    return _id;
}
