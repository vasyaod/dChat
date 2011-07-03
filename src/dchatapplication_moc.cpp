/****************************************************************************
** Meta object code from reading C++ file 'dchatapplication.h'
**
** Created: ?? 7. ??? 21:57:30 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dchatapplication.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dchatapplication.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dContextUserMenu[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      22,   18,   17,   17, 0x0a,
      48,   18,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dContextUserMenu[] = {
    "dContextUserMenu\0\0obj\0destroyedWidget(QObject*)\0"
    "destroyedAction(QObject*)\0"
};

const QMetaObject dContextUserMenu::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_dContextUserMenu,
      qt_meta_data_dContextUserMenu, 0 }
};

const QMetaObject *dContextUserMenu::metaObject() const
{
    return &staticMetaObject;
}

void *dContextUserMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dContextUserMenu))
	return static_cast<void*>(const_cast<dContextUserMenu*>(this));
    return QObject::qt_metacast(_clname);
}

int dContextUserMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: destroyedWidget(*reinterpret_cast< QObject**>(_a[1])); break;
        case 1: destroyedAction(*reinterpret_cast< QObject**>(_a[1])); break;
        }
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_dChatApplication[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      39,   17,   17,   17, 0x0a,
      55,   17,   17,   17, 0x0a,
      76,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dChatApplication[] = {
    "dChatApplication\0\0showPropertyWindow()\0showLogWindow()\0"
    "trayIconMouseClick()\0quitChat()\0"
};

const QMetaObject dChatApplication::staticMetaObject = {
    { &QApplication::staticMetaObject, qt_meta_stringdata_dChatApplication,
      qt_meta_data_dChatApplication, 0 }
};

const QMetaObject *dChatApplication::metaObject() const
{
    return &staticMetaObject;
}

void *dChatApplication::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dChatApplication))
	return static_cast<void*>(const_cast<dChatApplication*>(this));
    return QApplication::qt_metacast(_clname);
}

int dChatApplication::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QApplication::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: showPropertyWindow(); break;
        case 1: showLogWindow(); break;
        case 2: trayIconMouseClick(); break;
        case 3: quitChat(); break;
        }
        _id -= 4;
    }
    return _id;
}
static const uint qt_meta_data_dSettingStyle[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      20,   15,   14,   14, 0x0a,
      51,   44,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dSettingStyle[] = {
    "dSettingStyle\0\0text\0styleActivated(QString)\0_state\0"
    "startStateChanged(int)\0"
};

const QMetaObject dSettingStyle::staticMetaObject = {
    { &dSetting::staticMetaObject, qt_meta_stringdata_dSettingStyle,
      qt_meta_data_dSettingStyle, 0 }
};

const QMetaObject *dSettingStyle::metaObject() const
{
    return &staticMetaObject;
}

void *dSettingStyle::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dSettingStyle))
	return static_cast<void*>(const_cast<dSettingStyle*>(this));
    return dSetting::qt_metacast(_clname);
}

int dSettingStyle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = dSetting::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: styleActivated(*reinterpret_cast< QString*>(_a[1])); break;
        case 1: startStateChanged(*reinterpret_cast< int*>(_a[1])); break;
        }
        _id -= 2;
    }
    return _id;
}
