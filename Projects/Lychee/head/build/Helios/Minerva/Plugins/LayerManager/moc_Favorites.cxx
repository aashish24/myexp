/****************************************************************************
** Meta object code from reading C++ file 'Favorites.h'
**
** Created: Thu Apr 30 11:46:41 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Minerva/Plugins/LayerManager/Favorites.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Favorites.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Favorites[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      17,   11,   10,   10, 0x0a,
      55,   10,   10,   10, 0x08,
      90,   86,   10,   10, 0x08,
     117,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Favorites[] = {
    "Favorites\0\0layer\0addLayer(Usul::Interfaces::IUnknown*)\0"
    "_removeFavoriteButtonClicked()\0pos\0"
    "_onContextMenuShow(QPoint)\0_buildTree()\0"
};

const QMetaObject Favorites::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Favorites,
      qt_meta_data_Favorites, 0 }
};

const QMetaObject *Favorites::metaObject() const
{
    return &staticMetaObject;
}

void *Favorites::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Favorites))
        return static_cast<void*>(const_cast< Favorites*>(this));
    return QWidget::qt_metacast(_clname);
}

int Favorites::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: addLayer((*reinterpret_cast< Usul::Interfaces::IUnknown*(*)>(_a[1]))); break;
        case 1: _removeFavoriteButtonClicked(); break;
        case 2: _onContextMenuShow((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 3: _buildTree(); break;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
