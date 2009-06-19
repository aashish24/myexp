/****************************************************************************
** Meta object code from reading C++ file 'AddOssimLayerWidget.h'
**
** Created: Thu Apr 30 11:46:41 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Minerva/Plugins/OssimLayerQt/AddOssimLayerWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AddOssimLayerWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AddOssimLayerWidget[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x08,
      38,   20,   20,   20, 0x08,
      64,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AddOssimLayerWidget[] = {
    "AddOssimLayerWidget\0\0_browseClicked()\0"
    "_searchDirectoryClicked()\0"
    "_removeSelectedFiles()\0"
};

const QMetaObject AddOssimLayerWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AddOssimLayerWidget,
      qt_meta_data_AddOssimLayerWidget, 0 }
};

const QMetaObject *AddOssimLayerWidget::metaObject() const
{
    return &staticMetaObject;
}

void *AddOssimLayerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AddOssimLayerWidget))
        return static_cast<void*>(const_cast< AddOssimLayerWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int AddOssimLayerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _browseClicked(); break;
        case 1: _searchDirectoryClicked(); break;
        case 2: _removeSelectedFiles(); break;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
