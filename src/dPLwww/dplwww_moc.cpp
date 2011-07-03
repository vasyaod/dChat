/****************************************************************************
** Meta object code from reading C++ file 'dplwww.h'
**
** Created: ?? 29. ??? 00:46:21 2005
**      by: The Qt Meta Object Compiler version 58 (Qt 4.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dplwww.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dplwww.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 58
#error "This file was generated using the moc from 4.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dPlGoWWW[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dPlGoWWW[] = {
    "dPlGoWWW\0\0goWWW()\0"
};

const QMetaObject dPlGoWWW::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_dPlGoWWW,
      qt_meta_data_dPlGoWWW, 0 }
};

const QMetaObject *dPlGoWWW::metaObject() const
{
    return &staticMetaObject;
}

void *dPlGoWWW::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dPlGoWWW))
	return static_cast<void*>(const_cast<dPlGoWWW*>(this));
    if (!strcmp(_clname, "dChatPluginInterface"))
	return static_cast<dChatPluginInterface*>(const_cast<dPlGoWWW*>(this));
    if (!strcmp(_clname, "dChatPluginInterface/1.0"))
	return static_cast<dChatPluginInterface*>(const_cast<dPlGoWWW*>(this));
    return QObject::qt_metacast(_clname);
}

int dPlGoWWW::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: goWWW(); break;
        }
        _id -= 1;
    }
    return _id;
}
