/****************************************************************************
** Meta object code from reading C++ file 'dpixmapbutton.h'
**
** Created: ?? 3. ??? 07:55:43 2005
**      by: The Qt Meta Object Compiler version 58 (Qt 4.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dpixmapbutton.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dpixmapbutton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 58
#error "This file was generated using the moc from 4.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dPixmapButton[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      25,   14,   14,   14, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_dPixmapButton[] = {
    "dPixmapButton\0\0clicked()\0pressed()\0"
};

const QMetaObject dPixmapButton::staticMetaObject = {
    { &dPixmapView::staticMetaObject, qt_meta_stringdata_dPixmapButton,
      qt_meta_data_dPixmapButton, 0 }
};

const QMetaObject *dPixmapButton::metaObject() const
{
    return &staticMetaObject;
}

void *dPixmapButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dPixmapButton))
	return static_cast<void*>(const_cast<dPixmapButton*>(this));
    return dPixmapView::qt_metacast(_clname);
}

int dPixmapButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = dPixmapView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clicked(); break;
        case 1: pressed(); break;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void dPixmapButton::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
};

// SIGNAL 1
void dPixmapButton::pressed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
};
