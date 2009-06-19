/****************************************************************************
** Meta object code from reading C++ file 'TreeNode.h'
**
** Created: Thu Apr 30 11:45:10 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../QtTools/TreeNode.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TreeNode.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtTools__TreeNode[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QtTools__TreeNode[] = {
    "QtTools::TreeNode\0\0_onDataChanged(ulong)\0"
};

const QMetaObject QtTools::TreeNode::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QtTools__TreeNode,
      qt_meta_data_QtTools__TreeNode, 0 }
};

const QMetaObject *QtTools::TreeNode::metaObject() const
{
    return &staticMetaObject;
}

void *QtTools::TreeNode::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtTools__TreeNode))
        return static_cast<void*>(const_cast< TreeNode*>(this));
    if (!strcmp(_clname, "Usul::Interfaces::IDataChangedListener"))
        return static_cast< Usul::Interfaces::IDataChangedListener*>(const_cast< TreeNode*>(this));
    return QObject::qt_metacast(_clname);
}

int QtTools::TreeNode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _onDataChanged((*reinterpret_cast< ulong(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
