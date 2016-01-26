/****************************************************************************
** Meta object code from reading C++ file 'pictlabel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../pictlabel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pictlabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PictLabel_t {
    QByteArrayData data[7];
    char stringdata0[131];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PictLabel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PictLabel_t qt_meta_stringdata_PictLabel = {
    {
QT_MOC_LITERAL(0, 0, 9), // "PictLabel"
QT_MOC_LITERAL(1, 10, 20), // "signalNewPixelPicked"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 22), // "signalResizingRequired"
QT_MOC_LITERAL(4, 55, 23), // "signalRedisplayRequired"
QT_MOC_LITERAL(5, 79, 20), // "signalUndoVivibility"
QT_MOC_LITERAL(6, 100, 30) // "signalValidateCancelVivibility"

    },
    "PictLabel\0signalNewPixelPicked\0\0"
    "signalResizingRequired\0signalRedisplayRequired\0"
    "signalUndoVivibility\0"
    "signalValidateCancelVivibility"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PictLabel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,
       4,    0,   41,    2, 0x06 /* Public */,
       5,    0,   42,    2, 0x06 /* Public */,
       6,    0,   43,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PictLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PictLabel *_t = static_cast<PictLabel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalNewPixelPicked(); break;
        case 1: _t->signalResizingRequired(); break;
        case 2: _t->signalRedisplayRequired(); break;
        case 3: _t->signalUndoVivibility(); break;
        case 4: _t->signalValidateCancelVivibility(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PictLabel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PictLabel::signalNewPixelPicked)) {
                *result = 0;
            }
        }
        {
            typedef void (PictLabel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PictLabel::signalResizingRequired)) {
                *result = 1;
            }
        }
        {
            typedef void (PictLabel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PictLabel::signalRedisplayRequired)) {
                *result = 2;
            }
        }
        {
            typedef void (PictLabel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PictLabel::signalUndoVivibility)) {
                *result = 3;
            }
        }
        {
            typedef void (PictLabel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PictLabel::signalValidateCancelVivibility)) {
                *result = 4;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject PictLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_PictLabel.data,
      qt_meta_data_PictLabel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PictLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PictLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PictLabel.stringdata0))
        return static_cast<void*>(const_cast< PictLabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int PictLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
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
void PictLabel::signalNewPixelPicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void PictLabel::signalResizingRequired()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void PictLabel::signalRedisplayRequired()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void PictLabel::signalUndoVivibility()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void PictLabel::signalValidateCancelVivibility()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
