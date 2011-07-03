/****************************************************************************
** Meta object code from reading C++ file 'dlocalcommanduserex.h'
**
** Created: ?? 13. ??? 19:01:12 2006
**      by: The Qt Meta Object Compiler version 58 (Qt 4.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dlocalcommanduserex.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dlocalcommanduserex.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 58
#error "This file was generated using the moc from 4.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dLocalCommandUserEx[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x0a,
      57,   47,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dLocalCommandUserEx[] = {
    "dLocalCommandUserEx\0\0readyReadStandardOutput()\0_exitCode\0"
    "finishedProcess(int)\0"
};

const QMetaObject dLocalCommandUserEx::staticMetaObject = {
    { &dLocalUserEx::staticMetaObject, qt_meta_stringdata_dLocalCommandUserEx,
      qt_meta_data_dLocalCommandUserEx, 0 }
};

const QMetaObject *dLocalCommandUserEx::metaObject() const
{
    return &staticMetaObject;
}

void *dLocalCommandUserEx::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dLocalCommandUserEx))
	return static_cast<void*>(const_cast<dLocalCommandUserEx*>(this));
    return dLocalUserEx::qt_metacast(_clname);
}

int dLocalCommandUserEx::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = dLocalUserEx::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: readyReadStandardOutput(); break;
        case 1: finishedProcess(*(int*)_a[1]); break;
        }
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_dSettingCommandLocalUserEx[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      38,   28,   27,   27, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dSettingCommandLocalUserEx[] = {
    "dSettingCommandLocalUserEx\0\0_inemName\0commandEdited(QString)\0"
};

const QMetaObject dSettingCommandLocalUserEx::staticMetaObject = {
    { &dSetting::staticMetaObject, qt_meta_stringdata_dSettingCommandLocalUserEx,
      qt_meta_data_dSettingCommandLocalUserEx, 0 }
};

const QMetaObject *dSettingCommandLocalUserEx::metaObject() const
{
    return &staticMetaObject;
}

void *dSettingCommandLocalUserEx::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dSettingCommandLocalUserEx))
	return static_cast<void*>(const_cast<dSettingCommandLocalUserEx*>(this));
    return dSetting::qt_metacast(_clname);
}

int dSettingCommandLocalUserEx::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = dSetting::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: commandEdited(*(QString*)_a[1]); break;
        }
        _id -= 1;
    }
    return _id;
}
