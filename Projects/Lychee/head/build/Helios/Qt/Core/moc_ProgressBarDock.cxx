/****************************************************************************
** Meta object code from reading C++ file 'ProgressBarDock.h'
**
** Created: Thu Apr 30 11:45:27 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ProgressBarDock.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ProgressBarDock.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CadKit__Helios__Core__ProgressBarDock[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      39,   38,   38,   38, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_CadKit__Helios__Core__ProgressBarDock[] = {
    "CadKit::Helios::Core::ProgressBarDock\0"
    "\0_updateProgressBars()\0"
};

const QMetaObject CadKit::Helios::Core::ProgressBarDock::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CadKit__Helios__Core__ProgressBarDock,
      qt_meta_data_CadKit__Helios__Core__ProgressBarDock, 0 }
};

const QMetaObject *CadKit::Helios::Core::ProgressBarDock::metaObject() const
{
    return &staticMetaObject;
}

void *CadKit::Helios::Core::ProgressBarDock::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CadKit__Helios__Core__ProgressBarDock))
        return static_cast<void*>(const_cast< ProgressBarDock*>(this));
    if (!strcmp(_clname, "Usul::Base::Object"))
        return static_cast< Usul::Base::Object*>(const_cast< ProgressBarDock*>(this));
    return QObject::qt_metacast(_clname);
}

int CadKit::Helios::Core::ProgressBarDock::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _updateProgressBars(); break;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
