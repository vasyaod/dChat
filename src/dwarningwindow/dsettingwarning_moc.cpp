/****************************************************************************
** Meta object code from reading C++ file 'dsettingwarning.h'
**
** Created: ?? 22. ??? 01:09:10 2005
**      by: The Qt Meta Object Compiler version 58 (Qt 4.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dsettingwarning.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dsettingwarning.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 58
#error "This file was generated using the moc from 4.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dSettingWarning[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      23,   17,   16,   16, 0x0a,
      48,   17,   16,   16, 0x0a,
      78,   16,   16,   16, 0x0a,
      96,   16,   16,   16, 0x0a,
     117,  110,   16,   16, 0x0a,
     134,  110,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dSettingWarning[] = {
    "dSettingWarning\0\0state\0stateChangedWarning(int)\0"
    "stateChangedSoundWarning(int)\0fileSoundChange()\0colorChange()\0_value\0"
    "timeChanged(int)\0maxWindowChanged(int)\0"
};

const QMetaObject dSettingWarning::staticMetaObject = {
    { &dSetting::staticMetaObject, qt_meta_stringdata_dSettingWarning,
      qt_meta_data_dSettingWarning, 0 }
};

const QMetaObject *dSettingWarning::metaObject() const
{
    return &staticMetaObject;
}

void *dSettingWarning::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dSettingWarning))
	return static_cast<void*>(const_cast<dSettingWarning*>(this));
    return dSetting::qt_metacast(_clname);
}

int dSettingWarning::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = dSetting::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: stateChangedWarning(*(int*)_a[1]); break;
        case 1: stateChangedSoundWarning(*(int*)_a[1]); break;
        case 2: fileSoundChange(); break;
        case 3: colorChange(); break;
        case 4: timeChanged(*(int*)_a[1]); break;
        case 5: maxWindowChanged(*(int*)_a[1]); break;
        }
        _id -= 6;
    }
    return _id;
}
