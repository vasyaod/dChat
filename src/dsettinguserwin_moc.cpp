/****************************************************************************
** Meta object code from reading C++ file 'dsettinguserwin.h'
**
** Created: ?? 7. ??? 22:02:12 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dsettinguserwin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dsettinguserwin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dSettingUserWin[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      24,   17,   16,   16, 0x0a,
      53,   17,   16,   16, 0x0a,
      82,   17,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dSettingUserWin[] = {
    "dSettingUserWin\0\0_index\0sizeIconToIconActivated(int)\0"
    "sizeIconToListActivated(int)\0sizeIconToTableActivated(int)\0"
};

const QMetaObject dSettingUserWin::staticMetaObject = {
    { &dSetting::staticMetaObject, qt_meta_stringdata_dSettingUserWin,
      qt_meta_data_dSettingUserWin, 0 }
};

const QMetaObject *dSettingUserWin::metaObject() const
{
    return &staticMetaObject;
}

void *dSettingUserWin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dSettingUserWin))
	return static_cast<void*>(const_cast<dSettingUserWin*>(this));
    return dSetting::qt_metacast(_clname);
}

int dSettingUserWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = dSetting::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sizeIconToIconActivated(*reinterpret_cast< int*>(_a[1])); break;
        case 1: sizeIconToListActivated(*reinterpret_cast< int*>(_a[1])); break;
        case 2: sizeIconToTableActivated(*reinterpret_cast< int*>(_a[1])); break;
        }
        _id -= 3;
    }
    return _id;
}
