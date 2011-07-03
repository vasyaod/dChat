/****************************************************************************
** Meta object code from reading C++ file 'dwindowframe.h'
**
** Created: ?? 3. ??? 07:55:36 2005
**      by: The Qt Meta Object Compiler version 58 (Qt 4.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dwindowframe.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dwindowframe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 58
#error "This file was generated using the moc from 4.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dWindowFrame[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      26,   13,   13,   13, 0x05,
      38,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      47,   13,   13,   13, 0x09,
      67,   13,   13,   13, 0x09,
      87,   13,   13,   13, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_dWindowFrame[] = {
    "dWindowFrame\0\0minimized()\0maximized()\0closed()\0pressMinimizedKey()\0"
    "pressMaximizedKey()\0pressClosedKey()\0"
};

const QMetaObject dWindowFrame::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_dWindowFrame,
      qt_meta_data_dWindowFrame, 0 }
};

const QMetaObject *dWindowFrame::metaObject() const
{
    return &staticMetaObject;
}

void *dWindowFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dWindowFrame))
	return static_cast<void*>(const_cast<dWindowFrame*>(this));
    if (!strcmp(_clname, "dWindowFrame/1.0"))
	return static_cast<dWindowFrame*>(const_cast<dWindowFrame*>(this));
    return QWidget::qt_metacast(_clname);
}

int dWindowFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: minimized(); break;
        case 1: maximized(); break;
        case 2: closed(); break;
        case 3: pressMinimizedKey(); break;
        case 4: pressMaximizedKey(); break;
        case 5: pressClosedKey(); break;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void dWindowFrame::minimized()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
};

// SIGNAL 1
void dWindowFrame::maximized()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
};

// SIGNAL 2
void dWindowFrame::closed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
};
