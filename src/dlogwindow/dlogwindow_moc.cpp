/****************************************************************************
** Meta object code from reading C++ file 'dlogwindow.h'
**
** Created: ?? 12. ??? 19:32:27 2006
**      by: The Qt Meta Object Compiler version 58 (Qt 4.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dlogwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dlogwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 58
#error "This file was generated using the moc from 4.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dLogWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      17,   12,   11,   11, 0x0a,
      64,   55,   11,   11, 0x0a,
      93,   86,   11,   11, 0x0a,
     117,  110,   11,   11, 0x0a,
     145,   11,   11,   11, 0x0a,
     167,  156,   11,   11, 0x0a,
     200,  156,   11,   11, 0x0a,
     243,  236,   11,   11, 0x0a,
     276,  270,   11,   11, 0x0a,
     299,  270,   11,   11, 0x0a,
     331,  321,   11,   11, 0x0a,
     381,  360,   11,   11, 0x0a,
     427,  360,   11,   11, 0x0a,
     484,  469,   11,   11, 0x0a,
     531,  516,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dLogWindow[] = {
    "dLogWindow\0\0item\0tableDoubleClicked(QTableWidgetItem*)\0_checked\0"
    "closeSideWindow(bool)\0_index\0itemChanged(int)\0_state\0"
    "doubleMassStateChanged(int)\0clearLog()\0_from,_msg\0"
    "slot_msg_channel(dPUser,QString)\0slot_msg_channel_me(dPUser,QString)\0"
    "_topic\0slot_change_topic(QString)\0_from\0slot_msg_enter(dPUser)\0"
    "slot_msg_exit(dPUser)\0_from,_to\0slot_msg_beep(dPUser,dPUser)\0"
    "_from,_to,_msg,_html\0slot_msg_personal(dPUser,dPUser,QString,bool)\0"
    "slot_msg_mass(dPUser,dPUser,QString,bool)\0_from,_oldname\0"
    "slot_msg_rename(dPUser,QString)\0_from,_to,_msg\0"
    "slot_msg_auto_answer(dPUser,dPUser,QString)\0"
};

const QMetaObject dLogWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_dLogWindow,
      qt_meta_data_dLogWindow, 0 }
};

const QMetaObject *dLogWindow::metaObject() const
{
    return &staticMetaObject;
}

void *dLogWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dLogWindow))
	return static_cast<void*>(const_cast<dLogWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int dLogWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: tableDoubleClicked(*(QTableWidgetItem**)_a[1]); break;
        case 1: closeSideWindow(*(bool*)_a[1]); break;
        case 2: itemChanged(*(int*)_a[1]); break;
        case 3: doubleMassStateChanged(*(int*)_a[1]); break;
        case 4: clearLog(); break;
        case 5: slot_msg_channel(*(dPUser*)_a[1],*(QString*)_a[2]); break;
        case 6: slot_msg_channel_me(*(dPUser*)_a[1],*(QString*)_a[2]); break;
        case 7: slot_change_topic(*(QString*)_a[1]); break;
        case 8: slot_msg_enter(*(dPUser*)_a[1]); break;
        case 9: slot_msg_exit(*(dPUser*)_a[1]); break;
        case 10: slot_msg_beep(*(dPUser*)_a[1],*(dPUser*)_a[2]); break;
        case 11: slot_msg_personal(*(dPUser*)_a[1],*(dPUser*)_a[2],*(QString*)_a[3],*(bool*)_a[4]); break;
        case 12: slot_msg_mass(*(dPUser*)_a[1],*(dPUser*)_a[2],*(QString*)_a[3],*(bool*)_a[4]); break;
        case 13: slot_msg_rename(*(dPUser*)_a[1],*(QString*)_a[2]); break;
        case 14: slot_msg_auto_answer(*(dPUser*)_a[1],*(dPUser*)_a[2],*(QString*)_a[3]); break;
        }
        _id -= 15;
    }
    return _id;
}
