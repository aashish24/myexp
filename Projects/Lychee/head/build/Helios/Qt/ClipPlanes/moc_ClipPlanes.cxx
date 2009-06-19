/****************************************************************************
** Meta object code from reading C++ file 'ClipPlanes.h'
**
** Created: Thu Apr 30 11:45:35 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Plugins/ClipPlanes/ClipPlanes.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ClipPlanes.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClipPlanes[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x09,
      35,   11,   11,   11, 0x09,
      61,   11,   11,   11, 0x09,
      89,   11,   11,   11, 0x09,
     121,   11,   11,   11, 0x09,
     147,   11,   11,   11, 0x09,
     169,   11,   11,   11, 0x09,
     191,   11,   11,   11, 0x09,
     213,   11,   11,   11, 0x09,
     235,   11,   11,   11, 0x09,
     257,   11,   11,   11, 0x09,
     279,   11,   11,   11, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ClipPlanes[] = {
    "ClipPlanes\0\0_addClipPlaneClicked()\0"
    "_removeClipPlaneClicked()\0"
    "_distanceSliderChanged(int)\0"
    "_distanceSpinBoxChanged(double)\0"
    "_selectedItemChanged(int)\0"
    "on_posXAxis_clicked()\0on_posYAxis_clicked()\0"
    "on_posZAxis_clicked()\0on_negXAxis_clicked()\0"
    "on_negYAxis_clicked()\0on_negZAxis_clicked()\0"
    "on_clearButton_clicked()\0"
};

const QMetaObject ClipPlanes::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ClipPlanes,
      qt_meta_data_ClipPlanes, 0 }
};

const QMetaObject *ClipPlanes::metaObject() const
{
    return &staticMetaObject;
}

void *ClipPlanes::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClipPlanes))
        return static_cast<void*>(const_cast< ClipPlanes*>(this));
    return QWidget::qt_metacast(_clname);
}

int ClipPlanes::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _addClipPlaneClicked(); break;
        case 1: _removeClipPlaneClicked(); break;
        case 2: _distanceSliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _distanceSpinBoxChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _selectedItemChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: on_posXAxis_clicked(); break;
        case 6: on_posYAxis_clicked(); break;
        case 7: on_posZAxis_clicked(); break;
        case 8: on_negXAxis_clicked(); break;
        case 9: on_negYAxis_clicked(); break;
        case 10: on_negZAxis_clicked(); break;
        case 11: on_clearButton_clicked(); break;
        }
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
