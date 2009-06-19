/****************************************************************************
** Meta object code from reading C++ file 'BaseAddNetworkLayerWidget.h'
**
** Created: Thu Apr 30 11:46:41 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Minerva/Qt/Widgets/BaseAddNetworkLayerWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BaseAddNetworkLayerWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Minerva__Widgets__BaseAddNetworkLayerWidget[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      45,   44,   44,   44, 0x05,

 // slots: signature, parameters, type, tag, flags
      63,   44,   44,   44, 0x09,
      92,   44,   44,   44, 0x09,
     124,   44,   44,   44, 0x09,
     159,   44,   44,   44, 0x09,
     195,  190,   44,   44, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_Minerva__Widgets__BaseAddNetworkLayerWidget[] = {
    "Minerva::Widgets::BaseAddNetworkLayerWidget\0"
    "\0serverValid(bool)\0on_browseDirectory_clicked()\0"
    "on_capabilitiesButton_clicked()\0"
    "on_getServiceNamesButton_clicked()\0"
    "on_viewOptionsButton_clicked()\0text\0"
    "_onServerTextChanged(QString)\0"
};

const QMetaObject Minerva::Widgets::BaseAddNetworkLayerWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Minerva__Widgets__BaseAddNetworkLayerWidget,
      qt_meta_data_Minerva__Widgets__BaseAddNetworkLayerWidget, 0 }
};

const QMetaObject *Minerva::Widgets::BaseAddNetworkLayerWidget::metaObject() const
{
    return &staticMetaObject;
}

void *Minerva::Widgets::BaseAddNetworkLayerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Minerva__Widgets__BaseAddNetworkLayerWidget))
        return static_cast<void*>(const_cast< BaseAddNetworkLayerWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int Minerva::Widgets::BaseAddNetworkLayerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: serverValid((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: on_browseDirectory_clicked(); break;
        case 2: on_capabilitiesButton_clicked(); break;
        case 3: on_getServiceNamesButton_clicked(); break;
        case 4: on_viewOptionsButton_clicked(); break;
        case 5: _onServerTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Minerva::Widgets::BaseAddNetworkLayerWidget::serverValid(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
