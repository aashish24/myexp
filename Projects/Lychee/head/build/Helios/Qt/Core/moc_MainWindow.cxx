/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created: Thu Apr 30 11:45:27 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MainWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CadKit__Helios__Core__MainWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      34,   33,   33,   33, 0x08,
      55,   49,   33,   33, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CadKit__Helios__Core__MainWindow[] = {
    "CadKit::Helios::Core::MainWindow\0\0"
    "_idleProcess()\0proxy\0"
    "_notifyDocumentFinishedLoading(DocumentProxy)\0"
};

const QMetaObject CadKit::Helios::Core::MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_CadKit__Helios__Core__MainWindow,
      qt_meta_data_CadKit__Helios__Core__MainWindow, 0 }
};

const QMetaObject *CadKit::Helios::Core::MainWindow::metaObject() const
{
    return &staticMetaObject;
}

void *CadKit::Helios::Core::MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CadKit__Helios__Core__MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    if (!strcmp(_clname, "Usul::Interfaces::ILoadFileDialog"))
        return static_cast< Usul::Interfaces::ILoadFileDialog*>(const_cast< MainWindow*>(this));
    if (!strcmp(_clname, "Usul::Interfaces::ISaveFileDialog"))
        return static_cast< Usul::Interfaces::ISaveFileDialog*>(const_cast< MainWindow*>(this));
    if (!strcmp(_clname, "Usul::Interfaces::IUpdateTextWindow"))
        return static_cast< Usul::Interfaces::IUpdateTextWindow*>(const_cast< MainWindow*>(this));
    if (!strcmp(_clname, "Usul::Interfaces::Qt::IMainWindow"))
        return static_cast< Usul::Interfaces::Qt::IMainWindow*>(const_cast< MainWindow*>(this));
    if (!strcmp(_clname, "Usul::Interfaces::Qt::IWorkspace"))
        return static_cast< Usul::Interfaces::Qt::IWorkspace*>(const_cast< MainWindow*>(this));
    if (!strcmp(_clname, "Usul::Interfaces::IGUIDelegateNotify"))
        return static_cast< Usul::Interfaces::IGUIDelegateNotify*>(const_cast< MainWindow*>(this));
    if (!strcmp(_clname, "Usul::Interfaces::IStreamListenerChar"))
        return static_cast< Usul::Interfaces::IStreamListenerChar*>(const_cast< MainWindow*>(this));
    if (!strcmp(_clname, "Usul::Interfaces::IProgressBarFactory"))
        return static_cast< Usul::Interfaces::IProgressBarFactory*>(const_cast< MainWindow*>(this));
    if (!strcmp(_clname, "Usul::Interfaces::IQtDockWidgetMenu"))
        return static_cast< Usul::Interfaces::IQtDockWidgetMenu*>(const_cast< MainWindow*>(this));
    if (!strcmp(_clname, "Usul::Interfaces::IActiveDocumentListener"))
        return static_cast< Usul::Interfaces::IActiveDocumentListener*>(const_cast< MainWindow*>(this));
    if (!strcmp(_clname, "Usul::Interfaces::IActiveViewListener"))
        return static_cast< Usul::Interfaces::IActiveViewListener*>(const_cast< MainWindow*>(this));
    if (!strcmp(_clname, "Usul::Interfaces::IQuestion"))
        return static_cast< Usul::Interfaces::IQuestion*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int CadKit::Helios::Core::MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _idleProcess(); break;
        case 1: _notifyDocumentFinishedLoading((*reinterpret_cast< DocumentProxy(*)>(_a[1]))); break;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
