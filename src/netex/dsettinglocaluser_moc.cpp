/****************************************************************************
** Meta object code from reading C++ file 'dsettinglocaluser.h'
**
** Created: ?? 12. ??? 09:44:19 2006
**      by: The Qt Meta Object Compiler version 58 (Qt 4.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dsettinglocaluser.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dsettinglocaluser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 58
#error "This file was generated using the moc from 4.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dSettingLocalUser[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      27,   19,   18,   18, 0x0a,
      53,   18,   18,   18, 0x0a,
      73,   66,   18,   18, 0x0a,
      94,   18,   18,   18, 0x0a,
     120,  114,   18,   18, 0x0a,
     145,  138,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dSettingLocalUser[] = {
    "dSettingLocalUser\0\0checked\0clickedAvatarButton(bool)\0nameEdited()\0"
    "_login\0loginEdited(QString)\0autoAnswerChanged()\0index\0"
    "sexActivated(int)\0_state\0passiveModeChanged(int)\0"
};

const QMetaObject dSettingLocalUser::staticMetaObject = {
    { &dSetting::staticMetaObject, qt_meta_stringdata_dSettingLocalUser,
      qt_meta_data_dSettingLocalUser, 0 }
};

const QMetaObject *dSettingLocalUser::metaObject() const
{
    return &staticMetaObject;
}

void *dSettingLocalUser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dSettingLocalUser))
	return static_cast<void*>(const_cast<dSettingLocalUser*>(this));
    return dSetting::qt_metacast(_clname);
}

int dSettingLocalUser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = dSetting::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clickedAvatarButton(*(bool*)_a[1]); break;
        case 1: nameEdited(); break;
        case 2: loginEdited(*(QString*)_a[1]); break;
        case 3: autoAnswerChanged(); break;
        case 4: sexActivated(*(int*)_a[1]); break;
        case 5: passiveModeChanged(*(int*)_a[1]); break;
        }
        _id -= 6;
    }
    return _id;
}
