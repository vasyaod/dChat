/****************************************************************************
** Meta object code from reading C++ file 'icestyle.h'
**
** Created: ?? 5. ??? 09:45:27 2005
**      by: The Qt Meta Object Compiler version 58 (Qt 4.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "icestyle.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'icestyle.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 58
#error "This file was generated using the moc from 4.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_IceStyle[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_IceStyle[] = {
    "IceStyle\0"
};

const QMetaObject IceStyle::staticMetaObject = {
    { &QWindowsStyle::staticMetaObject, qt_meta_stringdata_IceStyle,
      qt_meta_data_IceStyle, 0 }
};

const QMetaObject *IceStyle::metaObject() const
{
    return &staticMetaObject;
}

void *IceStyle::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IceStyle))
	return static_cast<void*>(const_cast<IceStyle*>(this));
    return QWindowsStyle::qt_metacast(_clname);
}

int IceStyle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWindowsStyle::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
