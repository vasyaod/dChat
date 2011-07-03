/****************************************************************************
** Meta object code from reading C++ file 'dmanagerex.h'
**
** Created: ?? 12. ??? 19:29:32 2006
**      by: The Qt Meta Object Compiler version 58 (Qt 4.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dmanagerex.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dmanagerex.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 58
#error "This file was generated using the moc from 4.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dManagerEx[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      19,   12,   11,   11, 0x05,
      55,   49,   11,   11, 0x05,
      86,   49,   11,   11, 0x05,
     113,   49,   11,   11, 0x05,
     138,   49,   11,   11, 0x05,
     177,  162,   11,   11, 0x05,
     232,  211,   11,   11, 0x05,
     295,  280,   11,   11, 0x25,
     349,  338,   11,   11, 0x05,
     394,  384,   11,   11, 0x05,
     425,  211,   11,   11, 0x05,
     469,  280,   11,   11, 0x25,
     515,  508,   11,   11, 0x05,
     544,  508,   11,   11, 0x05,
     574,  338,   11,   11, 0x05,
     612,  280,   11,   11, 0x05,
     658,  280,   11,   11, 0x05,
     698,  692,   11,   11, 0x05,
     725,  692,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_dManagerEx[] = {
    "dManagerEx\0\0_count\0signal_count_user_change(int)\0_from\0"
    "signal_change_activity(dPUser)\0signal_change_mode(dPUser)\0"
    "signal_msg_enter(dPUser)\0signal_msg_exit(dPUser)\0_from,_oldname\0"
    "signal_msg_rename(dPUser,QString)\0_from,_to,_msg,_html\0"
    "signal_msg_personal(dPUser,dPUser,QString,bool)\0_from,_to,_msg\0"
    "signal_msg_personal(dPUser,dPUser,QString)\0_from,_msg\0"
    "signal_msg_channel(dPUser,QString)\0_from,_to\0"
    "signal_msg_beep(dPUser,dPUser)\0"
    "signal_msg_mass(dPUser,dPUser,QString,bool)\0"
    "signal_msg_mass(dPUser,dPUser,QString)\0_topic\0"
    "signal_change_topic(QString)\0signal_current_topic(QString)\0"
    "signal_msg_channel_me(dPUser,QString)\0"
    "signal_msg_auto_answer(dPUser,dPUser,QString)\0"
    "signal_xml(dPUser,dPUser,QString)\0_user\0signal_delete_user(dPUser)\0"
    "signal_add_user(dPUser)\0"
};

const QMetaObject dManagerEx::staticMetaObject = {
    { &dManager::staticMetaObject, qt_meta_stringdata_dManagerEx,
      qt_meta_data_dManagerEx, 0 }
};

const QMetaObject *dManagerEx::metaObject() const
{
    return &staticMetaObject;
}

void *dManagerEx::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dManagerEx))
	return static_cast<void*>(const_cast<dManagerEx*>(this));
    return dManager::qt_metacast(_clname);
}

int dManagerEx::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = dManager::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: signal_count_user_change(*(int*)_a[1]); break;
        case 1: signal_change_activity(*(dPUser*)_a[1]); break;
        case 2: signal_change_mode(*(dPUser*)_a[1]); break;
        case 3: signal_msg_enter(*(dPUser*)_a[1]); break;
        case 4: signal_msg_exit(*(dPUser*)_a[1]); break;
        case 5: signal_msg_rename(*(dPUser*)_a[1],*(QString*)_a[2]); break;
        case 6: signal_msg_personal(*(dPUser*)_a[1],*(dPUser*)_a[2],*(QString*)_a[3],*(bool*)_a[4]); break;
        case 7: signal_msg_personal(*(dPUser*)_a[1],*(dPUser*)_a[2],*(QString*)_a[3]); break;
        case 8: signal_msg_channel(*(dPUser*)_a[1],*(QString*)_a[2]); break;
        case 9: signal_msg_beep(*(dPUser*)_a[1],*(dPUser*)_a[2]); break;
        case 10: signal_msg_mass(*(dPUser*)_a[1],*(dPUser*)_a[2],*(QString*)_a[3],*(bool*)_a[4]); break;
        case 11: signal_msg_mass(*(dPUser*)_a[1],*(dPUser*)_a[2],*(QString*)_a[3]); break;
        case 12: signal_change_topic(*(QString*)_a[1]); break;
        case 13: signal_current_topic(*(QString*)_a[1]); break;
        case 14: signal_msg_channel_me(*(dPUser*)_a[1],*(QString*)_a[2]); break;
        case 15: signal_msg_auto_answer(*(dPUser*)_a[1],*(dPUser*)_a[2],*(QString*)_a[3]); break;
        case 16: signal_xml(*(dPUser*)_a[1],*(dPUser*)_a[2],*(QString*)_a[3]); break;
        case 17: signal_delete_user(*(dPUser*)_a[1]); break;
        case 18: signal_add_user(*(dPUser*)_a[1]); break;
        }
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void dManagerEx::signal_count_user_change(int _t1)
{
    void *_a[] = { 0, (void*)&_t1 };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void dManagerEx::signal_change_activity(dPUser _t1)
{
    void *_a[] = { 0, (void*)&_t1 };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void dManagerEx::signal_change_mode(dPUser _t1)
{
    void *_a[] = { 0, (void*)&_t1 };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void dManagerEx::signal_msg_enter(dPUser _t1)
{
    void *_a[] = { 0, (void*)&_t1 };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void dManagerEx::signal_msg_exit(dPUser _t1)
{
    void *_a[] = { 0, (void*)&_t1 };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void dManagerEx::signal_msg_rename(dPUser _t1, const QString & _t2)
{
    void *_a[] = { 0, (void*)&_t1, (void*)&_t2 };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void dManagerEx::signal_msg_personal(dPUser _t1, dPUser _t2, const QString & _t3, bool _t4)
{
    void *_a[] = { 0, (void*)&_t1, (void*)&_t2, (void*)&_t3, (void*)&_t4 };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void dManagerEx::signal_msg_channel(dPUser _t1, const QString & _t2)
{
    void *_a[] = { 0, (void*)&_t1, (void*)&_t2 };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void dManagerEx::signal_msg_beep(dPUser _t1, dPUser _t2)
{
    void *_a[] = { 0, (void*)&_t1, (void*)&_t2 };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void dManagerEx::signal_msg_mass(dPUser _t1, dPUser _t2, const QString & _t3, bool _t4)
{
    void *_a[] = { 0, (void*)&_t1, (void*)&_t2, (void*)&_t3, (void*)&_t4 };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void dManagerEx::signal_change_topic(const QString & _t1)
{
    void *_a[] = { 0, (void*)&_t1 };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void dManagerEx::signal_current_topic(const QString & _t1)
{
    void *_a[] = { 0, (void*)&_t1 };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void dManagerEx::signal_msg_channel_me(dPUser _t1, const QString & _t2)
{
    void *_a[] = { 0, (void*)&_t1, (void*)&_t2 };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void dManagerEx::signal_msg_auto_answer(dPUser _t1, dPUser _t2, const QString & _t3)
{
    void *_a[] = { 0, (void*)&_t1, (void*)&_t2, (void*)&_t3 };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void dManagerEx::signal_xml(dPUser _t1, dPUser _t2, const QString & _t3)
{
    void *_a[] = { 0, (void*)&_t1, (void*)&_t2, (void*)&_t3 };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void dManagerEx::signal_delete_user(dPUser _t1)
{
    void *_a[] = { 0, (void*)&_t1 };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void dManagerEx::signal_add_user(dPUser _t1)
{
    void *_a[] = { 0, (void*)&_t1 };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}
