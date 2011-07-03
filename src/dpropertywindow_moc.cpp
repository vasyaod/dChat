/****************************************************************************
** Meta object code from reading C++ file 'dpropertywindow.h'
**
** Created: ?? 7. ??? 21:57:14 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dpropertywindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dpropertywindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dPropertyWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x0a,
      31,   16,   16,   16, 0x0a,
      54,   45,   16,   16, 0x0a,
      85,   76,   16,   16, 0x0a,
     106,   16,   16,   16, 0x0a,
     135,  118,   16,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_dPropertyWindow[] = {
    "dPropertyWindow\0\0openSetting()\0saveSetting()\0_checked\0"
    "closeSideWindow(bool)\0_setting\0goSetting(dSetting*)\0reParsing()\0"
    "current,previous\0itemChanged(QTreeWidgetItem*,QTreeWidgetItem*)\0"
};

const QMetaObject dPropertyWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_dPropertyWindow,
      qt_meta_data_dPropertyWindow, 0 }
};

const QMetaObject *dPropertyWindow::metaObject() const
{
    return &staticMetaObject;
}

void *dPropertyWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dPropertyWindow))
	return static_cast<void*>(const_cast<dPropertyWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int dPropertyWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: openSetting(); break;
        case 1: saveSetting(); break;
        case 2: closeSideWindow(*reinterpret_cast< bool*>(_a[1])); break;
        case 3: goSetting(*reinterpret_cast< dSetting**>(_a[1])); break;
        case 4: reParsing(); break;
        case 5: itemChanged(*reinterpret_cast< QTreeWidgetItem**>(_a[1]),*reinterpret_cast< QTreeWidgetItem**>(_a[2])); break;
        }
        _id -= 6;
    }
    return _id;
}
