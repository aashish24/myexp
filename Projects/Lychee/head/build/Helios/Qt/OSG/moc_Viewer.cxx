/****************************************************************************
** Meta object code from reading C++ file 'Viewer.h'
**
** Created: Thu Apr 30 11:45:36 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Views/OSG/Viewer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Viewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CadKit__Helios__Views__OSG__Viewer[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      36,   35,   35,   35, 0x08,
      58,   35,   35,   35, 0x08,
      75,   35,   35,   35, 0x08,
     102,   98,   35,   35, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CadKit__Helios__Views__OSG__Viewer[] = {
    "CadKit::Helios::Views::OSG::Viewer\0\0"
    "_onTimeoutAnimation()\0_onTimeoutSpin()\0"
    "_onTimeoutRenderLoop()\0pos\0"
    "_onContextMenuShow(QPoint)\0"
};

const QMetaObject CadKit::Helios::Views::OSG::Viewer::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_CadKit__Helios__Views__OSG__Viewer,
      qt_meta_data_CadKit__Helios__Views__OSG__Viewer, 0 }
};

const QMetaObject *CadKit::Helios::Views::OSG::Viewer::metaObject() const
{
    return &staticMetaObject;
}

void *CadKit::Helios::Views::OSG::Viewer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CadKit__Helios__Views__OSG__Viewer))
        return static_cast<void*>(const_cast< Viewer*>(this));
    if (!strcmp(_clname, "Usul::Interfaces::IOpenGLContext"))
        return static_cast< Usul::Interfaces::IOpenGLContext*>(const_cast< Viewer*>(this));
    if (!strcmp(_clname, "Usul::Interfaces::IWindow"))
        return static_cast< Usul::Interfaces::IWindow*>(const_cast< Viewer*>(this));
    if (!strcmp(_clname, "Usul::Interfaces::ITimeoutAnimate"))
        return static_cast< Usul::Interfaces::ITimeoutAnimate*>(const_cast< Viewer*>(this));
    if (!strcmp(_clname, "Usul::Interfaces::ITimeoutSpin"))
        return static_cast< Usul::Interfaces::ITimeoutSpin*>(const_cast< Viewer*>(this));
    if (!strcmp(_clname, "Usul::Interfaces::IModifiedObserver"))
        return static_cast< Usul::Interfaces::IModifiedObserver*>(const_cast< Viewer*>(this));
    if (!strcmp(_clname, "Usul::Interfaces::IRenderLoop"))
        return static_cast< Usul::Interfaces::IRenderLoop*>(const_cast< Viewer*>(this));
    if (!strcmp(_clname, "Usul::Interfaces::IRedraw"))
        return static_cast< Usul::Interfaces::IRedraw*>(const_cast< Viewer*>(this));
    if (!strcmp(_clname, "Usul::Interfaces::IMenuAdd"))
        return static_cast< Usul::Interfaces::IMenuAdd*>(const_cast< Viewer*>(this));
    if (!strcmp(_clname, "Usul::Interfaces::IQuestion"))
        return static_cast< Usul::Interfaces::IQuestion*>(const_cast< Viewer*>(this));
    if (!strcmp(_clname, "Usul::Interfaces::ISaveFileDialog"))
        return static_cast< Usul::Interfaces::ISaveFileDialog*>(const_cast< Viewer*>(this));
    if (!strcmp(_clname, "Usul::Interfaces::IToolBarAdd"))
        return static_cast< Usul::Interfaces::IToolBarAdd*>(const_cast< Viewer*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int CadKit::Helios::Views::OSG::Viewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _onTimeoutAnimation(); break;
        case 1: _onTimeoutSpin(); break;
        case 2: _onTimeoutRenderLoop(); break;
        case 3: _onContextMenuShow((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
