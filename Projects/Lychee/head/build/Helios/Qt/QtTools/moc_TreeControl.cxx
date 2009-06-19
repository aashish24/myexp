/****************************************************************************
** Meta object code from reading C++ file 'TreeControl.h'
**
** Created: Thu Apr 30 11:45:13 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../QtTools/TreeControl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TreeControl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtTools__TreeControl[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      27,   22,   21,   21, 0x05,
      56,   22,   21,   21, 0x05,
      91,   21,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
     114,  112,   21,   21, 0x08,
     152,   21,   21,   21, 0x08,
     182,  112,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QtTools__TreeControl[] = {
    "QtTools::TreeControl\0\0node\0"
    "onTreeNodeChanged(TreeNode*)\0"
    "onTreeNodeDoubleClicked(TreeNode*)\0"
    "onSelectionChanged()\0,\0"
    "_dataChanged(QModelIndex,QModelIndex)\0"
    "_onDoubleClicked(QModelIndex)\0"
    "_onCurrentChanged(QModelIndex,QModelIndex)\0"
};

const QMetaObject QtTools::TreeControl::staticMetaObject = {
    { &QTreeView::staticMetaObject, qt_meta_stringdata_QtTools__TreeControl,
      qt_meta_data_QtTools__TreeControl, 0 }
};

const QMetaObject *QtTools::TreeControl::metaObject() const
{
    return &staticMetaObject;
}

void *QtTools::TreeControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtTools__TreeControl))
        return static_cast<void*>(const_cast< TreeControl*>(this));
    return QTreeView::qt_metacast(_clname);
}

int QtTools::TreeControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onTreeNodeChanged((*reinterpret_cast< TreeNode*(*)>(_a[1]))); break;
        case 1: onTreeNodeDoubleClicked((*reinterpret_cast< TreeNode*(*)>(_a[1]))); break;
        case 2: onSelectionChanged(); break;
        case 3: _dataChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2]))); break;
        case 4: _onDoubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: _onCurrentChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2]))); break;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void QtTools::TreeControl::onTreeNodeChanged(TreeNode * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QtTools::TreeControl::onTreeNodeDoubleClicked(TreeNode * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QtTools::TreeControl::onSelectionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
