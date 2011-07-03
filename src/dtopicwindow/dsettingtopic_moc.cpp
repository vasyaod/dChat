/****************************************************************************
** Meta object code from reading C++ file 'dsettingtopic.h'
**
** Created: ?? 5. ??? 08:52:47 2005
**      by: The Qt Meta Object Compiler version 58 (Qt 4.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dsettingtopic.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dsettingtopic.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 58
#error "This file was generated using the moc from 4.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dSettingTopic[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      35,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dSettingTopic[] = {
    "dSettingTopic\0\0clickedFontButton()\0clickedStdFontButton()\0"
};

const QMetaObject dSettingTopic::staticMetaObject = {
    { &dSetting::staticMetaObject, qt_meta_stringdata_dSettingTopic,
      qt_meta_data_dSettingTopic, 0 }
};

const QMetaObject *dSettingTopic::metaObject() const
{
    return &staticMetaObject;
}

void *dSettingTopic::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dSettingTopic))
	return static_cast<void*>(const_cast<dSettingTopic*>(this));
    return dSetting::qt_metacast(_clname);
}

int dSettingTopic::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = dSetting::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clickedFontButton(); break;
        case 1: clickedStdFontButton(); break;
        }
        _id -= 2;
    }
    return _id;
}
