/****************************************************************************
** Meta object code from reading C++ file 'AlphasDialog.h'
**
** Created: Thu Apr 30 11:46:41 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Minerva/Qt/Widgets/AlphasDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AlphasDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Minerva__Widgets__AlphasDialog[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      32,   31,   31,   31, 0x09,
      58,   31,   31,   31, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_Minerva__Widgets__AlphasDialog[] = {
    "Minerva::Widgets::AlphasDialog\0\0"
    "on_addRowButton_clicked()\0"
    "on_removeRowButton_clicked()\0"
};

const QMetaObject Minerva::Widgets::AlphasDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Minerva__Widgets__AlphasDialog,
      qt_meta_data_Minerva__Widgets__AlphasDialog, 0 }
};

const QMetaObject *Minerva::Widgets::AlphasDialog::metaObject() const
{
    return &staticMetaObject;
}

void *Minerva::Widgets::AlphasDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Minerva__Widgets__AlphasDialog))
        return static_cast<void*>(const_cast< AlphasDialog*>(this));
    if (!strcmp(_clname, "Ui::AlphasDialog"))
        return static_cast< Ui::AlphasDialog*>(const_cast< AlphasDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int Minerva::Widgets::AlphasDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_addRowButton_clicked(); break;
        case 1: on_removeRowButton_clicked(); break;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
