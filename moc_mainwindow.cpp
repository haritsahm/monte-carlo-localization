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
    QByteArrayData data[29];
    char stringdata0[325];
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
QT_MOC_LITERAL(7, 46, 10), // "loadConfig"
QT_MOC_LITERAL(8, 57, 11), // "std::string"
QT_MOC_LITERAL(9, 69, 4), // "path"
QT_MOC_LITERAL(10, 74, 10), // "onWpressed"
QT_MOC_LITERAL(11, 85, 10), // "onApressed"
QT_MOC_LITERAL(12, 96, 10), // "onSpressed"
QT_MOC_LITERAL(13, 107, 10), // "onDpressed"
QT_MOC_LITERAL(14, 118, 10), // "onQpressed"
QT_MOC_LITERAL(15, 129, 10), // "onEpressed"
QT_MOC_LITERAL(16, 140, 15), // "updateRobotPose"
QT_MOC_LITERAL(17, 156, 13), // "setLinePoints"
QT_MOC_LITERAL(18, 170, 20), // "std::vector<QPointF>"
QT_MOC_LITERAL(19, 191, 10), // "linePoints"
QT_MOC_LITERAL(20, 202, 12), // "setParticles"
QT_MOC_LITERAL(21, 215, 9), // "Particles"
QT_MOC_LITERAL(22, 225, 9), // "particles"
QT_MOC_LITERAL(23, 235, 5), // "State"
QT_MOC_LITERAL(24, 241, 13), // "mean_estimate"
QT_MOC_LITERAL(25, 255, 30), // "on_menu_open_control_triggered"
QT_MOC_LITERAL(26, 286, 28), // "on_menu_loadconfig_triggered"
QT_MOC_LITERAL(27, 315, 7), // "setPose"
QT_MOC_LITERAL(28, 323, 1) // "w"

    },
    "MainWindow\0updateOdometry\0\0x\0y\0deg\0"
    "updatePose\0loadConfig\0std::string\0"
    "path\0onWpressed\0onApressed\0onSpressed\0"
    "onDpressed\0onQpressed\0onEpressed\0"
    "updateRobotPose\0setLinePoints\0"
    "std::vector<QPointF>\0linePoints\0"
    "setParticles\0Particles\0particles\0State\0"
    "mean_estimate\0on_menu_open_control_triggered\0"
    "on_menu_loadconfig_triggered\0setPose\0"
    "w"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   89,    2, 0x06 /* Public */,
       6,    3,   96,    2, 0x06 /* Public */,
       7,    1,  103,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,  106,    2, 0x0a /* Public */,
      11,    0,  107,    2, 0x0a /* Public */,
      12,    0,  108,    2, 0x0a /* Public */,
      13,    0,  109,    2, 0x0a /* Public */,
      14,    0,  110,    2, 0x0a /* Public */,
      15,    0,  111,    2, 0x0a /* Public */,
      16,    0,  112,    2, 0x0a /* Public */,
      17,    1,  113,    2, 0x0a /* Public */,
      20,    2,  116,    2, 0x0a /* Public */,
      25,    0,  121,    2, 0x0a /* Public */,
      26,    0,  122,    2, 0x0a /* Public */,
      27,    3,  123,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,    3,    4,    5,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,    3,    4,    5,
    QMetaType::Void, 0x80000000 | 8,    9,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, 0x80000000 | 21, 0x80000000 | 23,   22,   24,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,    3,    4,   28,

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
        case 2: _t->loadConfig((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 3: _t->onWpressed(); break;
        case 4: _t->onApressed(); break;
        case 5: _t->onSpressed(); break;
        case 6: _t->onDpressed(); break;
        case 7: _t->onQpressed(); break;
        case 8: _t->onEpressed(); break;
        case 9: _t->updateRobotPose(); break;
        case 10: _t->setLinePoints((*reinterpret_cast< std::vector<QPointF>(*)>(_a[1]))); break;
        case 11: _t->setParticles((*reinterpret_cast< Particles(*)>(_a[1])),(*reinterpret_cast< State(*)>(_a[2]))); break;
        case 12: _t->on_menu_open_control_triggered(); break;
        case 13: _t->on_menu_loadconfig_triggered(); break;
        case 14: _t->setPose((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
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
        {
            typedef void (MainWindow::*_t)(std::string );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::loadConfig)) {
                *result = 2;
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
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
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

// SIGNAL 2
void MainWindow::loadConfig(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
