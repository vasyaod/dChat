/****************************************************************************
** Meta object code from reading C++ file 'dlistviewex.h'
**
** Created: ?? 25. ??? 23:03:57 2005
**      by: The Qt Meta Object Compiler version 58 (Qt 4.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dlistviewex.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dlistviewex.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 58
#error "This file was generated using the moc from 4.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dListViewEx[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      30,   13,   12,   12, 0x09,
      72,   13,   12,   12, 0x09,
     126,  106,   12,   12, 0x09,
     180,  163,   12,   12, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_dListViewEx[] = {
    "dListViewEx\0\0parent,start,end\0"
    "rowsAboutToBeRemoved(QModelIndex,int,int)\0"
    "rowsInserted(QModelIndex,int,int)\0topLeft,bottomRight\0"
    "dataChanged(QModelIndex,QModelIndex)\0current,previous\0"
    "currentChanged(QModelIndex,QModelIndex)\0"
};

const QMetaObject dListViewEx::staticMetaObject = {
    { &QListView::staticMetaObject, qt_meta_stringdata_dListViewEx,
      qt_meta_data_dListViewEx, 0 }
};

const QMetaObject *dListViewEx::metaObject() const
{
    return &staticMetaObject;
}

void *dListViewEx::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dListViewEx))
	return static_cast<void*>(const_cast<dListViewEx*>(this));
    return QListView::qt_metacast(_clname);
}

int dListViewEx::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: rowsAboutToBeRemoved(*(QModelIndex*)_a[1],*(int*)_a[2],*(int*)_a[3]); break;
        case 1: rowsInserted(*(QModelIndex*)_a[1],*(int*)_a[2],*(int*)_a[3]); break;
        case 2: dataChanged(*(QModelIndex*)_a[1],*(QModelIndex*)_a[2]); break;
        case 3: currentChanged(*(QModelIndex*)_a[1],*(QModelIndex*)_a[2]); break;
        }
        _id -= 4;
    }
    return _id;
}
