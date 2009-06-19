/****************************************************************************
** Meta object code from reading C++ file 'PropertyBrowser.h'
**
** Created: Thu Apr 30 11:45:12 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../QtTools/PropertyBrowser.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PropertyBrowser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtTools__PropertyBrowser[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_QtTools__PropertyBrowser[] = {
    "QtTools::PropertyBrowser\0"
};

const QMetaObject QtTools::PropertyBrowser::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QtTools__PropertyBrowser,
      qt_meta_data_QtTools__PropertyBrowser, 0 }
};

const QMetaObject *QtTools::PropertyBrowser::metaObject() const
{
    return &staticMetaObject;
}

void *QtTools::PropertyBrowser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtTools__PropertyBrowser))
        return static_cast<void*>(const_cast< PropertyBrowser*>(this));
    return QWidget::qt_metacast(_clname);
}

int QtTools::PropertyBrowser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
