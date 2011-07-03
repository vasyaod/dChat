/****************************************************************************
** Meta object code from reading C++ file 'dwindow.h'
**
** Created: ?? 7. ??? 21:57:58 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      17,    9,    8,    8, 0x05,
      34,    8,    8,    8, 0x25,

 // slots: signature, parameters, type, tag, flags
      47,    8,    8,    8, 0x0a,
      54,    8,    8,    8, 0x0a,
      61,    8,    8,    8, 0x0a,
      78,   69,    8,    8, 0x0a,
     100,    8,   95,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dWindow[] = {
    "dWindow\0\0checked\0hideSignal(bool)\0hideSignal()\0hide()\0show()\0"
    "lower()\0_visible\0setVisible(bool)\0bool\0isVisible()\0"
};

const QMetaObject dWindow::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_dWindow,
      qt_meta_data_dWindow, 0 }
};

const QMetaObject *dWindow::metaObject() const
{
    return &staticMetaObject;
}

void *dWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dWindow))
	return static_cast<void*>(const_cast<dWindow*>(this));
    return QObject::qt_metacast(_clname);
}

int dWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: hideSignal(*reinterpret_cast< bool*>(_a[1])); break;
        case 1: hideSignal(); break;
        case 2: hide(); break;
        case 3: show(); break;
        case 4: lower(); break;
        case 5: setVisible(*reinterpret_cast< bool*>(_a[1])); break;
        case 6: { bool _r = isVisible();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void dWindow::hideSignal(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, 1, _a);
}
