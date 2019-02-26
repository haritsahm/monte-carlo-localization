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
#include <QtCore/QVector>
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
    QByteArrayData data[28];
    char stringdata0[280];
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
QT_MOC_LITERAL(11, 123, 12), // "publishParam"
QT_MOC_LITERAL(12, 136, 15), // "QVector<double>"
QT_MOC_LITERAL(13, 152, 5), // "param"
QT_MOC_LITERAL(14, 158, 14), // "updateOdometry"
QT_MOC_LITERAL(15, 173, 1), // "x"
QT_MOC_LITERAL(16, 175, 1), // "y"
QT_MOC_LITERAL(17, 177, 3), // "deg"
QT_MOC_LITERAL(18, 181, 10), // "updatePose"
QT_MOC_LITERAL(19, 192, 14), // "setMotionNoise"
QT_MOC_LITERAL(20, 207, 1), // "w"
QT_MOC_LITERAL(21, 209, 14), // "setVisionNoise"
QT_MOC_LITERAL(22, 224, 10), // "loadConfig"
QT_MOC_LITERAL(23, 235, 11), // "std::string"
QT_MOC_LITERAL(24, 247, 4), // "path"
QT_MOC_LITERAL(25, 252, 11), // "setMCLParam"
QT_MOC_LITERAL(26, 264, 8), // "resetMCL"
QT_MOC_LITERAL(27, 273, 6) // "status"

    },
    "MCL\0publishPoints\0\0std::vector<QPointF>\0"
    "linePoints\0publishMeanEst\0State\0"
    "mean_estimate\0publishParticles\0Particles\0"
    "particles\0publishParam\0QVector<double>\0"
    "param\0updateOdometry\0x\0y\0deg\0updatePose\0"
    "setMotionNoise\0w\0setVisionNoise\0"
    "loadConfig\0std::string\0path\0setMCLParam\0"
    "resetMCL\0status"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MCL[] = {

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
       1,    1,   69,    2, 0x06 /* Public */,
       5,    1,   72,    2, 0x06 /* Public */,
       8,    2,   75,    2, 0x06 /* Public */,
      11,    1,   80,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    3,   83,    2, 0x0a /* Public */,
      18,    3,   90,    2, 0x0a /* Public */,
      19,    3,   97,    2, 0x0a /* Public */,
      21,    2,  104,    2, 0x0a /* Public */,
      22,    1,  109,    2, 0x0a /* Public */,
      25,    1,  112,    2, 0x0a /* Public */,
      26,    1,  115,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 6,   10,    7,
    QMetaType::Void, 0x80000000 | 12,   13,

 // slots: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,   15,   16,   17,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,   15,   16,   17,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,   15,   16,   20,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   15,   16,
    QMetaType::Void, 0x80000000 | 23,   24,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, QMetaType::Bool,   27,

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
        case 3: _t->publishParam((*reinterpret_cast< QVector<double>(*)>(_a[1]))); break;
        case 4: _t->updateOdometry((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 5: _t->updatePose((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 6: _t->setMotionNoise((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 7: _t->setVisionNoise((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 8: _t->loadConfig((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 9: _t->setMCLParam((*reinterpret_cast< QVector<double>(*)>(_a[1]))); break;
        case 10: _t->resetMCL((*reinterpret_cast< bool(*)>(_a[1]))); break;
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
        case 9:
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
        {
            typedef void (MCL::*_t)(QVector<double> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MCL::publishParam)) {
                *result = 3;
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

// SIGNAL 3
void MCL::publishParam(QVector<double> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
