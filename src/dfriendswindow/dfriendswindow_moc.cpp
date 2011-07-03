/****************************************************************************
** Meta object code from reading C++ file 'dfriendswindow.h'
**
** Created: ?? 27. ??? 02:32:36 2005
**      by: The Qt Meta Object Compiler version 58 (Qt 4.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dfriendswindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dfriendswindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 58
#error "This file was generated using the moc from 4.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dFriendsWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x0a,
      37,   15,   15,   15, 0x0a,
      53,   15,   15,   15, 0x0a,
      67,   15,   15,   15, 0x0a,
      88,   82,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dFriendsWindow[] = {
    "dFriendsWindow\0\0addFriendNameAndIP()\0addFriendName()\0addFriendIP()\0"
    "deleteFriend()\0index\0itemDoubleClicked(QModelIndex)\0"
};

const QMetaObject dFriendsWindow::staticMetaObject = {
    { &dWindow::staticMetaObject, qt_meta_stringdata_dFriendsWindow,
      qt_meta_data_dFriendsWindow, 0 }
};

const QMetaObject *dFriendsWindow::metaObject() const
{
    return &staticMetaObject;
}

void *dFriendsWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dFriendsWindow))
	return static_cast<void*>(const_cast<dFriendsWindow*>(this));
    return dWindow::qt_metacast(_clname);
}

int dFriendsWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = dWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: addFriendNameAndIP(); break;
        case 1: addFriendName(); break;
        case 2: addFriendIP(); break;
        case 3: deleteFriend(); break;
        case 4: itemDoubleClicked(*(QModelIndex*)_a[1]); break;
        }
        _id -= 5;
    }
    return _id;
}
