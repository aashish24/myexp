/****************************************************************************
** Meta object code from reading C++ file 'AnimationControl.h'
**
** Created: Thu Apr 30 11:45:11 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../QtTools/AnimationControl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AnimationControl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtTools__AnimationControl[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      27,   26,   26,   26, 0x09,
      41,   26,   26,   26, 0x09,
      58,   26,   26,   26, 0x09,
      76,   26,   26,   26, 0x09,
      98,   26,   26,   26, 0x09,
     122,   26,   26,   26, 0x09,
     139,   26,   26,   26, 0x09,
     157,   26,   26,   26, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QtTools__AnimationControl[] = {
    "QtTools::AnimationControl\0\0_onLoop(bool)\0"
    "_onPlayForward()\0_onPlayBackward()\0"
    "_onSliderChanged(int)\0_onSpeedChanged(double)\0"
    "_onStepForward()\0_onStepBackward()\0"
    "_onStopPlaying()\0"
};

const QMetaObject QtTools::AnimationControl::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QtTools__AnimationControl,
      qt_meta_data_QtTools__AnimationControl, 0 }
};

const QMetaObject *QtTools::AnimationControl::metaObject() const
{
    return &staticMetaObject;
}

void *QtTools::AnimationControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtTools__AnimationControl))
        return static_cast<void*>(const_cast< AnimationControl*>(this));
    if (!strcmp(_clname, "Usul::Interfaces::IActiveDocumentListener"))
        return static_cast< Usul::Interfaces::IActiveDocumentListener*>(const_cast< AnimationControl*>(this));
    if (!strcmp(_clname, "Usul::Interfaces::IModifiedObserver"))
        return static_cast< Usul::Interfaces::IModifiedObserver*>(const_cast< AnimationControl*>(this));
    if (!strcmp(_clname, "Usul::Interfaces::ITimerNotify"))
        return static_cast< Usul::Interfaces::ITimerNotify*>(const_cast< AnimationControl*>(this));
    return QWidget::qt_metacast(_clname);
}

int QtTools::AnimationControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _onLoop((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _onPlayForward(); break;
        case 2: _onPlayBackward(); break;
        case 3: _onSliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _onSpeedChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _onStepForward(); break;
        case 6: _onStepBackward(); break;
        case 7: _onStopPlaying(); break;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
