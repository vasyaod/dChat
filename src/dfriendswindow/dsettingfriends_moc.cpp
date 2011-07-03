/****************************************************************************
** Meta object code from reading C++ file 'dsettingfriends.h'
**
** Created: ?? 13. ??? 04:02:23 2005
**      by: The Qt Meta Object Compiler version 58 (Qt 4.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dsettingfriends.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dsettingfriends.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 58
#error "This file was generated using the moc from 4.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dSettingFriends[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dSettingFriends[] = {
    "dSettingFriends\0\0clickedDeleteButton()\0"
};

const QMetaObject dSettingFriends::staticMetaObject = {
    { &dSetting::staticMetaObject, qt_meta_stringdata_dSettingFriends,
      qt_meta_data_dSettingFriends, 0 }
};

const QMetaObject *dSettingFriends::metaObject() const
{
    return &staticMetaObject;
}

void *dSettingFriends::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dSettingFriends))
	return static_cast<void*>(const_cast<dSettingFriends*>(this));
    return dSetting::qt_metacast(_clname);
}

int dSettingFriends::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = dSetting::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clickedDeleteButton(); break;
        }
        _id -= 1;
    }
    return _id;
}
