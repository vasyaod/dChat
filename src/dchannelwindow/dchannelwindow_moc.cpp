/****************************************************************************
** Meta object code from reading C++ file 'dchannelwindow.h'
**
** Created: ?? 21. ??? 15:54:42 2005
**      by: The Qt Meta Object Compiler version 58 (Qt 4.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dchannelwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dchannelwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 58
#error "This file was generated using the moc from 4.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dChannelWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      22,   16,   15,   15, 0x0a,
      56,   45,   15,   15, 0x0a,
      87,   77,   15,   15, 0x0a,
     114,   77,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dChannelWindow[] = {
    "dChannelWindow\0\0_name\0addNameToEdit(QString)\0_clickable\0"
    "settingToggled(bool)\0_usr,_msg\0addMessage(dPUser,QString)\0"
    "addMessageMe(dPUser,QString)\0"
};

const QMetaObject dChannelWindow::staticMetaObject = {
    { &dWindow::staticMetaObject, qt_meta_stringdata_dChannelWindow,
      qt_meta_data_dChannelWindow, 0 }
};

const QMetaObject *dChannelWindow::metaObject() const
{
    return &staticMetaObject;
}

void *dChannelWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dChannelWindow))
	return static_cast<void*>(const_cast<dChannelWindow*>(this));
    return dWindow::qt_metacast(_clname);
}

int dChannelWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = dWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: addNameToEdit(*(QString*)_a[1]); break;
        case 1: settingToggled(*(bool*)_a[1]); break;
        case 2: addMessage(*(dPUser*)_a[1],*(QString*)_a[2]); break;
        case 3: addMessageMe(*(dPUser*)_a[1],*(QString*)_a[2]); break;
        }
        _id -= 4;
    }
    return _id;
}
