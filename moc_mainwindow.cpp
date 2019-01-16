/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[22];
    char stringdata0[227];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 14), // "updateOdometry"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 1), // "x"
QT_MOC_LITERAL(4, 29, 1), // "y"
QT_MOC_LITERAL(5, 31, 3), // "deg"
QT_MOC_LITERAL(6, 35, 10), // "updatePose"
QT_MOC_LITERAL(7, 46, 10), // "onWpressed"
QT_MOC_LITERAL(8, 57, 10), // "onApressed"
QT_MOC_LITERAL(9, 68, 10), // "onSpressed"
QT_MOC_LITERAL(10, 79, 10), // "onDpressed"
QT_MOC_LITERAL(11, 90, 10), // "onQpressed"
QT_MOC_LITERAL(12, 101, 10), // "onEpressed"
QT_MOC_LITERAL(13, 112, 15), // "updateRobotPose"
QT_MOC_LITERAL(14, 128, 13), // "setLinePoints"
QT_MOC_LITERAL(15, 142, 20), // "std::vector<QPointF>"
QT_MOC_LITERAL(16, 163, 10), // "linePoints"
QT_MOC_LITERAL(17, 174, 12), // "setParticles"
QT_MOC_LITERAL(18, 187, 9), // "Particles"
QT_MOC_LITERAL(19, 197, 9), // "particles"
QT_MOC_LITERAL(20, 207, 5), // "State"
QT_MOC_LITERAL(21, 213, 13) // "mean_estimate"

    },
    "MainWindow\0updateOdometry\0\0x\0y\0deg\0"
    "updatePose\0onWpressed\0onApressed\0"
    "onSpressed\0onDpressed\0onQpressed\0"
    "onEpressed\0updateRobotPose\0setLinePoints\0"
    "std::vector<QPointF>\0linePoints\0"
    "setParticles\0Particles\0particles\0State\0"
    "mean_estimate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   69,    2, 0x06 /* Public */,
       6,    3,   76,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   83,    2, 0x0a /* Public */,
       8,    0,   84,    2, 0x0a /* Public */,
       9,    0,   85,    2, 0x0a /* Public */,
      10,    0,   86,    2, 0x0a /* Public */,
      11,    0,   87,    2, 0x0a /* Public */,
      12,    0,   88,    2, 0x0a /* Public */,
      13,    0,   89,    2, 0x0a /* Public */,
      14,    1,   90,    2, 0x0a /* Public */,
      17,    2,   93,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,    3,    4,    5,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,    3,    4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 18, 0x80000000 | 20,   19,   21,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateOdometry((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 1: _t->updatePose((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 2: _t->onWpressed(); break;
        case 3: _t->onApressed(); break;
        case 4: _t->onSpressed(); break;
        case 5: _t->onDpressed(); break;
        case 6: _t->onQpressed(); break;
        case 7: _t->onEpressed(); break;
        case 8: _t->updateRobotPose(); break;
        case 9: _t->setLinePoints((*reinterpret_cast< std::vector<QPointF>(*)>(_a[1]))); break;
        case 10: _t->setParticles((*reinterpret_cast< Particles(*)>(_a[1])),(*reinterpret_cast< State(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(double , double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::updateOdometry)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(double , double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::updatePose)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::updateOdometry(double _t1, double _t2, double _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::updatePose(double _t1, double _t2, double _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
