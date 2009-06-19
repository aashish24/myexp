/****************************************************************************
** Meta object code from reading C++ file 'EditWmsLayerWidget.h'
**
** Created: Thu Apr 30 11:46:54 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Minerva/Plugins/WmsLayerQt/EditWmsLayerWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EditWmsLayerWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EditWmsLayerWidget[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x09,
      43,   19,   19,   19, 0x09,
      68,   19,   19,   19, 0x09,
      99,   19,   19,   19, 0x09,
     129,   19,   19,   19, 0x09,
     158,   19,   19,   19, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_EditWmsLayerWidget[] = {
    "EditWmsLayerWidget\0\0_nameFinishedEditing()\0"
    "_serverFinishedEditing()\0"
    "on_viewOptionsButton_clicked()\0"
    "on_viewAlphasButton_clicked()\0"
    "on_viewCacheButton_clicked()\0"
    "on_deleteCacheButton_clicked()\0"
};

const QMetaObject EditWmsLayerWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_EditWmsLayerWidget,
      qt_meta_data_EditWmsLayerWidget, 0 }
};

const QMetaObject *EditWmsLayerWidget::metaObject() const
{
    return &staticMetaObject;
}

void *EditWmsLayerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EditWmsLayerWidget))
        return static_cast<void*>(const_cast< EditWmsLayerWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int EditWmsLayerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _nameFinishedEditing(); break;
        case 1: _serverFinishedEditing(); break;
        case 2: on_viewOptionsButton_clicked(); break;
        case 3: on_viewAlphasButton_clicked(); break;
        case 4: on_viewCacheButton_clicked(); break;
        case 5: on_deleteCacheButton_clicked(); break;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
