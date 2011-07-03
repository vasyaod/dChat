/****************************************************************************
** Meta object code from reading C++ file 'dwarningwindow.h'
**
** Created: ?? 21. ??? 14:29:18 2005
**      by: The Qt Meta Object Compiler version 58 (Qt 4.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dwarningwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dwarningwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 58
#error "This file was generated using the moc from 4.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dWarningWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      27,   16,   15,   15, 0x0a,
      60,   16,   15,   15, 0x0a,
     103,   96,   15,   15, 0x0a,
     136,  130,   15,   15, 0x0a,
     159,  130,   15,   15, 0x0a,
     191,  181,   15,   15, 0x0a,
     235,  220,   15,   15, 0x0a,
     276,  220,   15,   15, 0x0a,
     328,  313,   15,   15, 0x0a,
     360,  220,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dWarningWindow[] = {
    "dWarningWindow\0\0_from,_msg\0slot_msg_channel(dPUser,QString)\0"
    "slot_msg_channel_me(dPUser,QString)\0_topic\0slot_change_topic(QString)\0"
    "_from\0slot_msg_enter(dPUser)\0slot_msg_exit(dPUser)\0_from,_to\0"
    "slot_msg_beep(dPUser,dPUser)\0_from,_to,_msg\0"
    "slot_msg_personal(dPUser,dPUser,QString)\0"
    "slot_msg_mass(dPUser,dPUser,QString)\0_from,_oldname\0"
    "slot_msg_rename(dPUser,QString)\0slot_msg_other(dPUser,dPUser,QString)\0"
};

const QMetaObject dWarningWindow::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_dWarningWindow,
      qt_meta_data_dWarningWindow, 0 }
};

const QMetaObject *dWarningWindow::metaObject() const
{
    return &staticMetaObject;
}

void *dWarningWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dWarningWindow))
	return static_cast<void*>(const_cast<dWarningWindow*>(this));
    return QObject::qt_metacast(_clname);
}

int dWarningWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slot_msg_channel(*(dPUser*)_a[1],*(QString*)_a[2]); break;
        case 1: slot_msg_channel_me(*(dPUser*)_a[1],*(QString*)_a[2]); break;
        case 2: slot_change_topic(*(QString*)_a[1]); break;
        case 3: slot_msg_enter(*(dPUser*)_a[1]); break;
        case 4: slot_msg_exit(*(dPUser*)_a[1]); break;
        case 5: slot_msg_beep(*(dPUser*)_a[1],*(dPUser*)_a[2]); break;
        case 6: slot_msg_personal(*(dPUser*)_a[1],*(dPUser*)_a[2],*(QString*)_a[3]); break;
        case 7: slot_msg_mass(*(dPUser*)_a[1],*(dPUser*)_a[2],*(QString*)_a[3]); break;
        case 8: slot_msg_rename(*(dPUser*)_a[1],*(QString*)_a[2]); break;
        case 9: slot_msg_other(*(dPUser*)_a[1],*(dPUser*)_a[2],*(QString*)_a[3]); break;
        }
        _id -= 10;
    }
    return _id;
}
