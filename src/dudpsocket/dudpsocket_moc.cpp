/****************************************************************************
** Meta object code from reading C++ file 'dudpsocket.h'
**
** Created: ?? 8. ??? 04:07:10 2005
**      by: The Qt Meta Object Compiler version 58 (Qt 4.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dudpsocket.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dudpsocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 58
#error "This file was generated using the moc from 4.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dUdpSocket[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_dUdpSocket[] = {
    "dUdpSocket\0\0readyRead()\0"
};

const QMetaObject dUdpSocket::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_dUdpSocket,
      qt_meta_data_dUdpSocket, 0 }
};

const QMetaObject *dUdpSocket::metaObject() const
{
    return &staticMetaObject;
}

void *dUdpSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dUdpSocket))
	return static_cast<void*>(const_cast<dUdpSocket*>(this));
    if (!strcmp(_clname, "dUdpSocket/1.0"))
	return static_cast<dUdpSocket*>(const_cast<dUdpSocket*>(this));
    return QThread::qt_metacast(_clname);
}

int dUdpSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: readyRead(); break;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void dUdpSocket::readyRead()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
};
