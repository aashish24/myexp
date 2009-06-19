/****************************************************************************
** Meta object code from reading C++ file 'TimerCallback.h'
**
** Created: Thu Apr 30 11:45:27 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "TimerCallback.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TimerCallback.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CadKit__Helios__Core__TimerCallback[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      37,   36,   36,   36, 0x08,
      50,   36,   36,   36, 0x08,
      59,   36,   36,   36, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CadKit__Helios__Core__TimerCallback[] = {
    "CadKit::Helios::Core::TimerCallback\0"
    "\0_onTimeout()\0_start()\0_stop()\0"
};

const QMetaObject CadKit::Helios::Core::TimerCallback::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CadKit__Helios__Core__TimerCallback,
      qt_meta_data_CadKit__Helios__Core__TimerCallback, 0 }
};

const QMetaObject *CadKit::Helios::Core::TimerCallback::metaObject() const
{
    return &staticMetaObject;
}

void *CadKit::Helios::Core::TimerCallback::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CadKit__Helios__Core__TimerCallback))
        return static_cast<void*>(const_cast< TimerCallback*>(this));
    return QObject::qt_metacast(_clname);
}

int CadKit::Helios::Core::TimerCallback::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _onTimeout(); break;
        case 1: _start(); break;
        case 2: _stop(); break;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
