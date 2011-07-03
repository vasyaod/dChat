/****************************************************************************
** Meta object code from reading C++ file 'dsettingnet.h'
**
** Created: ?? 6. ??? 15:38:07 2005
**      by: The Qt Meta Object Compiler version 58 (Qt 4.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dsettingnet.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dsettingnet.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 58
#error "This file was generated using the moc from 4.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dSettingNet[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      22,   13,   12,   12, 0x0a,
      52,   45,   12,   12, 0x0a,
      72,   45,   12,   12, 0x0a,
      92,   45,   12,   12, 0x0a,
     116,   12,   12,   12, 0x0a,
     148,   12,   12,   12, 0x0a,
     174,   12,   12,   12, 0x0a,
     207,   12,   12,   12, 0x0a,
     234,   12,   12,   12, 0x0a,
     265,  258,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dSettingNet[] = {
    "dSettingNet\0\0_checked\0clickedUseButton(bool)\0_value\0"
    "timeoutChanged(int)\0refreshChanged(int)\0refreshInfoChanged(int)\0"
    "clickedAddRangeIPWindowButton()\0clickedAddRangeIPButton()\0"
    "clickedAddSingleIPWindowButton()\0clickedAddSingleIPButton()\0"
    "clickedDeleteIPButton()\0_index\0sendTypeActivated(int)\0"
};

const QMetaObject dSettingNet::staticMetaObject = {
    { &dSetting::staticMetaObject, qt_meta_stringdata_dSettingNet,
      qt_meta_data_dSettingNet, 0 }
};

const QMetaObject *dSettingNet::metaObject() const
{
    return &staticMetaObject;
}

void *dSettingNet::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dSettingNet))
	return static_cast<void*>(const_cast<dSettingNet*>(this));
    return dSetting::qt_metacast(_clname);
}

int dSettingNet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = dSetting::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clickedUseButton(*(bool*)_a[1]); break;
        case 1: timeoutChanged(*(int*)_a[1]); break;
        case 2: refreshChanged(*(int*)_a[1]); break;
        case 3: refreshInfoChanged(*(int*)_a[1]); break;
        case 4: clickedAddRangeIPWindowButton(); break;
        case 5: clickedAddRangeIPButton(); break;
        case 6: clickedAddSingleIPWindowButton(); break;
        case 7: clickedAddSingleIPButton(); break;
        case 8: clickedDeleteIPButton(); break;
        case 9: sendTypeActivated(*(int*)_a[1]); break;
        }
        _id -= 10;
    }
    return _id;
}
