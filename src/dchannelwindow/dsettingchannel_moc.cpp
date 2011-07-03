/****************************************************************************
** Meta object code from reading C++ file 'dsettingchannel.h'
**
** Created: ?? 5. ??? 07:30:34 2005
**      by: The Qt Meta Object Compiler version 58 (Qt 4.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dsettingchannel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dsettingchannel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 58
#error "This file was generated using the moc from 4.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dSettingChannel[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      24,   17,   16,   16, 0x0a,
      54,   47,   16,   16, 0x0a,
      77,   47,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dSettingChannel[] = {
    "dSettingChannel\0\0_index\0viewTypeActivated(int)\0_value\0"
    "messageMaxChanged(int)\0nameMaxChanged(int)\0"
};

const QMetaObject dSettingChannel::staticMetaObject = {
    { &dSetting::staticMetaObject, qt_meta_stringdata_dSettingChannel,
      qt_meta_data_dSettingChannel, 0 }
};

const QMetaObject *dSettingChannel::metaObject() const
{
    return &staticMetaObject;
}

void *dSettingChannel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dSettingChannel))
	return static_cast<void*>(const_cast<dSettingChannel*>(this));
    return dSetting::qt_metacast(_clname);
}

int dSettingChannel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = dSetting::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: viewTypeActivated(*(int*)_a[1]); break;
        case 1: messageMaxChanged(*(int*)_a[1]); break;
        case 2: nameMaxChanged(*(int*)_a[1]); break;
        }
        _id -= 3;
    }
    return _id;
}
