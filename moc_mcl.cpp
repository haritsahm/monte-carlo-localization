/****************************************************************************
** Meta object code from reading C++ file 'mcl.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mcl.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mcl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MCL_t {
    QByteArrayData data[16];
    char stringdata0[157];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MCL_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MCL_t qt_meta_stringdata_MCL = {
    {
QT_MOC_LITERAL(0, 0, 3), // "MCL"
QT_MOC_LITERAL(1, 4, 13), // "publishPoints"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 20), // "std::vector<QPointF>"
QT_MOC_LITERAL(4, 40, 10), // "linePoints"
QT_MOC_LITERAL(5, 51, 14), // "publishMeanEst"
QT_MOC_LITERAL(6, 66, 5), // "State"
QT_MOC_LITERAL(7, 72, 13), // "mean_estimate"
QT_MOC_LITERAL(8, 86, 16), // "publishParticles"
QT_MOC_LITERAL(9, 103, 9), // "Particles"
QT_MOC_LITERAL(10, 113, 9), // "particles"
QT_MOC_LITERAL(11, 123, 14), // "updateOdometry"
QT_MOC_LITERAL(12, 138, 1), // "x"
QT_MOC_LITERAL(13, 140, 1), // "y"
QT_MOC_LITERAL(14, 142, 3), // "deg"
QT_MOC_LITERAL(15, 146, 10) // "updatePose"

    },
    "MCL\0publishPoints\0\0std::vector<QPointF>\0"
    "linePoints\0publishMeanEst\0State\0"
    "mean_estimate\0publishParticles\0Particles\0"
    "particles\0updateOdometry\0x\0y\0deg\0"
    "updatePose"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MCL[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       5,    1,   42,    2, 0x06 /* Public */,
       8,    2,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    3,   50,    2, 0x0a /* Public */,
      15,    3,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 6,   10,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,   12,   13,   14,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,   12,   13,   14,

       0        // eod
};

void MCL::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MCL *_t = static_cast<MCL *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->publishPoints((*reinterpret_cast< std::vector<QPointF>(*)>(_a[1]))); break;
        case 1: _t->publishMeanEst((*reinterpret_cast< State(*)>(_a[1]))); break;
        case 2: _t->publishParticles((*reinterpret_cast< Particles(*)>(_a[1])),(*reinterpret_cast< State(*)>(_a[2]))); break;
        case 3: _t->updateOdometry((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 4: _t->updatePose((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MCL::*_t)(std::vector<QPointF> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MCL::publishPoints)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MCL::*_t)(State );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MCL::publishMeanEst)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MCL::*_t)(Particles , State );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MCL::publishParticles)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject MCL::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MCL.data,
      qt_meta_data_MCL,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MCL::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MCL::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MCL.stringdata0))
        return static_cast<void*>(const_cast< MCL*>(this));
    return QObject::qt_metacast(_clname);
}

int MCL::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void MCL::publishPoints(std::vector<QPointF> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MCL::publishMeanEst(State _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MCL::publishParticles(Particles _t1, State _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
