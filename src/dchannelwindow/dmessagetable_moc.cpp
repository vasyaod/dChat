/****************************************************************************
** Meta object code from reading C++ file 'dmessagetable.h'
**
** Created: ?? 5. ??? 07:39:50 2005
**      by: The Qt Meta Object Compiler version 58 (Qt 4.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dmessagetable.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dmessagetable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 58
#error "This file was generated using the moc from 4.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dMessageTable[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      21,   15,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      57,   44,   14,   14, 0x0a,
      88,   77,   14,   14, 0x0a,
     107,   77,   14,   14, 0x0a,
     131,   77,   14,   14, 0x0a,
     156,   77,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dMessageTable[] = {
    "dMessageTable\0\0_name\0addNameSignal(QString)\0logicalIndex\0"
    "sectionClicked(int)\0_clickable\0clearToggled(bool)\0"
    "findToListToggled(bool)\0sendMessageToggled(bool)\0"
    "sendBeepToggled(bool)\0"
};

const QMetaObject dMessageTable::staticMetaObject = {
    { &QTableWidget::staticMetaObject, qt_meta_stringdata_dMessageTable,
      qt_meta_data_dMessageTable, 0 }
};

const QMetaObject *dMessageTable::metaObject() const
{
    return &staticMetaObject;
}

void *dMessageTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dMessageTable))
	return static_cast<void*>(const_cast<dMessageTable*>(this));
    return QTableWidget::qt_metacast(_clname);
}

int dMessageTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: addNameSignal(*(QString*)_a[1]); break;
        case 1: sectionClicked(*(int*)_a[1]); break;
        case 2: clearToggled(*(bool*)_a[1]); break;
        case 3: findToListToggled(*(bool*)_a[1]); break;
        case 4: sendMessageToggled(*(bool*)_a[1]); break;
        case 5: sendBeepToggled(*(bool*)_a[1]); break;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void dMessageTable::addNameSignal(const QString & _t1)
{
    void *_a[] = { 0, (void*)&_t1 };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
