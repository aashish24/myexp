/****************************************************************************
** Meta object code from reading C++ file 'PasswordPromptComponent.h'
**
** Created: Thu Apr 30 11:44:57 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Qt/Plugins/PasswordPrompt/PasswordPromptComponent.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PasswordPromptComponent.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PasswordPromptComponent[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      30,   25,   24,   24, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PasswordPromptComponent[] = {
    "PasswordPromptComponent\0\0text\0"
    "_promptForPassword(QString)\0"
};

const QMetaObject PasswordPromptComponent::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PasswordPromptComponent,
      qt_meta_data_PasswordPromptComponent, 0 }
};

const QMetaObject *PasswordPromptComponent::metaObject() const
{
    return &staticMetaObject;
}

void *PasswordPromptComponent::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PasswordPromptComponent))
        return static_cast<void*>(const_cast< PasswordPromptComponent*>(this));
    if (!strcmp(_clname, "Usul::Base::Object"))
        return static_cast< Usul::Base::Object*>(const_cast< PasswordPromptComponent*>(this));
    if (!strcmp(_clname, "Usul::Interfaces::IPlugin"))
        return static_cast< Usul::Interfaces::IPlugin*>(const_cast< PasswordPromptComponent*>(this));
    if (!strcmp(_clname, "Usul::Interfaces::IPasswordPrompt"))
        return static_cast< Usul::Interfaces::IPasswordPrompt*>(const_cast< PasswordPromptComponent*>(this));
    return QObject::qt_metacast(_clname);
}

int PasswordPromptComponent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _promptForPassword((*reinterpret_cast< QString(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
