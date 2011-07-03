/****************************************************************************
** Meta object code from reading C++ file 'dtopicwindow.h'
**
** Created: ?? 5. ??? 08:10:52 2005
**      by: The Qt Meta Object Compiler version 58 (Qt 4.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dtopicwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dtopicwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 58
#error "This file was generated using the moc from 4.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dTopicWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      21,   14,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dTopicWindow[] = {
    "dTopicWindow\0\0_topic\0setTopic(QString)\0"
};

const QMetaObject dTopicWindow::staticMetaObject = {
    { &dWindow::staticMetaObject, qt_meta_stringdata_dTopicWindow,
      qt_meta_data_dTopicWindow, 0 }
};

const QMetaObject *dTopicWindow::metaObject() const
{
    return &staticMetaObject;
}

void *dTopicWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dTopicWindow))
	return static_cast<void*>(const_cast<dTopicWindow*>(this));
    return dWindow::qt_metacast(_clname);
}

int dTopicWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = dWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setTopic(*(QString*)_a[1]); break;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_dTopicTextEditEx[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dTopicTextEditEx[] = {
    "dTopicTextEditEx\0\0clickedSendButton()\0"
};

const QMetaObject dTopicTextEditEx::staticMetaObject = {
    { &QTextEdit::staticMetaObject, qt_meta_stringdata_dTopicTextEditEx,
      qt_meta_data_dTopicTextEditEx, 0 }
};

const QMetaObject *dTopicTextEditEx::metaObject() const
{
    return &staticMetaObject;
}

void *dTopicTextEditEx::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dTopicTextEditEx))
	return static_cast<void*>(const_cast<dTopicTextEditEx*>(this));
    return QTextEdit::qt_metacast(_clname);
}

int dTopicTextEditEx::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clickedSendButton(); break;
        }
        _id -= 1;
    }
    return _id;
}
