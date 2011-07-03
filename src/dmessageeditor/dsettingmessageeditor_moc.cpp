/****************************************************************************
** Meta object code from reading C++ file 'dsettingmessageeditor.h'
**
** Created: ?? 25. ??? 17:45:13 2005
**      by: The Qt Meta Object Compiler version 58 (Qt 4.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dsettingmessageeditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dsettingmessageeditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 58
#error "This file was generated using the moc from 4.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dSettingMessageEditor[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      27,   23,   22,   22, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dSettingMessageEditor[] = {
    "dSettingMessageEditor\0\0_on\0quotingToggled(bool)\0"
};

const QMetaObject dSettingMessageEditor::staticMetaObject = {
    { &dSetting::staticMetaObject, qt_meta_stringdata_dSettingMessageEditor,
      qt_meta_data_dSettingMessageEditor, 0 }
};

const QMetaObject *dSettingMessageEditor::metaObject() const
{
    return &staticMetaObject;
}

void *dSettingMessageEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dSettingMessageEditor))
	return static_cast<void*>(const_cast<dSettingMessageEditor*>(this));
    return dSetting::qt_metacast(_clname);
}

int dSettingMessageEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = dSetting::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: quotingToggled(*(bool*)_a[1]); break;
        }
        _id -= 1;
    }
    return _id;
}
