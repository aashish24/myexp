/****************************************************************************
** Meta object code from reading C++ file 'ColorButton.h'
**
** Created: Thu Apr 30 11:45:12 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../QtTools/ColorButton.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ColorButton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtTools__ColorButton[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x05,
      41,   37,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
      80,   21,   21,   21, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QtTools__ColorButton[] = {
    "QtTools::ColorButton\0\0colorChanged()\0"
    ",,,\0colorChangedF(float,float,float,float)\0"
    "_buttonClicked()\0"
};

const QMetaObject QtTools::ColorButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_QtTools__ColorButton,
      qt_meta_data_QtTools__ColorButton, 0 }
};

const QMetaObject *QtTools::ColorButton::metaObject() const
{
    return &staticMetaObject;
}

void *QtTools::ColorButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtTools__ColorButton))
        return static_cast<void*>(const_cast< ColorButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int QtTools::ColorButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: colorChanged(); break;
        case 1: colorChangedF((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 2: _buttonClicked(); break;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void QtTools::ColorButton::colorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QtTools::ColorButton::colorChangedF(float _t1, float _t2, float _t3, float _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
