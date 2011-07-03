/****************************************************************************
** Meta object code from reading C++ file 'dmessageeditor.h'
**
** Created: ?? 29. ??? 03:28:23 2005
**      by: The Qt Meta Object Compiler version 58 (Qt 4.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dmessageeditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dmessageeditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 58
#error "This file was generated using the moc from 4.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dMessageEditor[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x0a,
      46,   36,   15,   15, 0x0a,
      69,   15,   15,   15, 0x0a,
      80,   15,   15,   15, 0x0a,
      96,   15,   15,   15, 0x0a,
     109,   15,   15,   15, 0x0a,
     131,  129,   15,   15, 0x0a,
     153,  151,   15,   15, 0x0a,
     171,   15,   15,   15, 0x0a,
     183,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dMessageEditor[] = {
    "dMessageEditor\0\0clickedSendButton()\0pos,index\0"
    "splitterMoved(int,int)\0textBold()\0textUnderline()\0textItalic()\0"
    "textAlign(QAction*)\0f\0textFamily(QString)\0p\0textSize(QString)\0"
    "textColor()\0saveMessage()\0"
};

const QMetaObject dMessageEditor::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_dMessageEditor,
      qt_meta_data_dMessageEditor, 0 }
};

const QMetaObject *dMessageEditor::metaObject() const
{
    return &staticMetaObject;
}

void *dMessageEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dMessageEditor))
	return static_cast<void*>(const_cast<dMessageEditor*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int dMessageEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clickedSendButton(); break;
        case 1: splitterMoved(*(int*)_a[1],*(int*)_a[2]); break;
        case 2: textBold(); break;
        case 3: textUnderline(); break;
        case 4: textItalic(); break;
        case 5: textAlign(*(QAction**)_a[1]); break;
        case 6: textFamily(*(QString*)_a[1]); break;
        case 7: textSize(*(QString*)_a[1]); break;
        case 8: textColor(); break;
        case 9: saveMessage(); break;
        }
        _id -= 10;
    }
    return _id;
}
