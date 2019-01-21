/****************************************************************************
** Meta object code from reading C++ file 'control.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "control.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'control.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Control_t {
    QByteArrayData data[20];
    char stringdata0[288];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Control_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Control_t qt_meta_stringdata_Control = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Control"
QT_MOC_LITERAL(1, 8, 7), // "setPose"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 1), // "x"
QT_MOC_LITERAL(4, 19, 1), // "y"
QT_MOC_LITERAL(5, 21, 1), // "w"
QT_MOC_LITERAL(6, 23, 14), // "setMotionNoise"
QT_MOC_LITERAL(7, 38, 14), // "setVisionNoise"
QT_MOC_LITERAL(8, 53, 11), // "setMCLParam"
QT_MOC_LITERAL(9, 65, 15), // "QVector<double>"
QT_MOC_LITERAL(10, 81, 5), // "param"
QT_MOC_LITERAL(11, 87, 33), // "on_button_setnoise_vision_cli..."
QT_MOC_LITERAL(12, 121, 2), // "ck"
QT_MOC_LITERAL(13, 124, 33), // "on_button_setnoise_motion_cli..."
QT_MOC_LITERAL(14, 158, 30), // "on_button_mcl_setparam_clicked"
QT_MOC_LITERAL(15, 189, 2), // "ok"
QT_MOC_LITERAL(16, 192, 27), // "on_button_mcl_reset_clicked"
QT_MOC_LITERAL(17, 220, 27), // "on_button_robot_set_clicked"
QT_MOC_LITERAL(18, 248, 30), // "on_button_robot_random_clicked"
QT_MOC_LITERAL(19, 279, 8) // "setParam"

    },
    "Control\0setPose\0\0x\0y\0w\0setMotionNoise\0"
    "setVisionNoise\0setMCLParam\0QVector<double>\0"
    "param\0on_button_setnoise_vision_clicked\0"
    "ck\0on_button_setnoise_motion_clicked\0"
    "on_button_mcl_setparam_clicked\0ok\0"
    "on_button_mcl_reset_clicked\0"
    "on_button_robot_set_clicked\0"
    "on_button_robot_random_clicked\0setParam"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Control[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   69,    2, 0x06 /* Public */,
       6,    3,   76,    2, 0x06 /* Public */,
       7,    2,   83,    2, 0x06 /* Public */,
       8,    1,   88,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    1,   91,    2, 0x0a /* Public */,
      13,    1,   94,    2, 0x0a /* Public */,
      14,    1,   97,    2, 0x0a /* Public */,
      16,    1,  100,    2, 0x0a /* Public */,
      17,    1,  103,    2, 0x0a /* Public */,
      18,    1,  106,    2, 0x0a /* Public */,
      19,    1,  109,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,    3,    4,    5,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,    3,    4,    5,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    3,    4,
    QMetaType::Void, 0x80000000 | 9,   10,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, 0x80000000 | 9,   10,

       0        // eod
};

void Control::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Control *_t = static_cast<Control *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setPose((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 1: _t->setMotionNoise((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 2: _t->setVisionNoise((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 3: _t->setMCLParam((*reinterpret_cast< QVector<double>(*)>(_a[1]))); break;
        case 4: _t->on_button_setnoise_vision_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_button_setnoise_motion_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_button_mcl_setparam_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_button_mcl_reset_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_button_robot_set_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_button_robot_random_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->setParam((*reinterpret_cast< QVector<double>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<double> >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<double> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Control::*_t)(double , double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Control::setPose)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Control::*_t)(double , double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Control::setMotionNoise)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Control::*_t)(double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Control::setVisionNoise)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Control::*_t)(QVector<double> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Control::setMCLParam)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject Control::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Control.data,
      qt_meta_data_Control,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Control::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Control::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Control.stringdata0))
        return static_cast<void*>(const_cast< Control*>(this));
    return QWidget::qt_metacast(_clname);
}

int Control::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void Control::setPose(double _t1, double _t2, double _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Control::setMotionNoise(double _t1, double _t2, double _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Control::setVisionNoise(double _t1, double _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Control::setMCLParam(QVector<double> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
