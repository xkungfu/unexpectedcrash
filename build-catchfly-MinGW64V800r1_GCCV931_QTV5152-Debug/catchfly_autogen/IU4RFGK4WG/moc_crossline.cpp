/****************************************************************************
** Meta object code from reading C++ file 'crossline.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../../CXXlibs/QCUSTOMPLOT/common1.0/crossline.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'crossline.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CrossLine_t {
    QByteArrayData data[14];
    char stringdata0[138];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CrossLine_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CrossLine_t qt_meta_stringdata_CrossLine = {
    {
QT_MOC_LITERAL(0, 0, 9), // "CrossLine"
QT_MOC_LITERAL(1, 10, 12), // "onMouseMoved"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 12), // "QMouseEvent*"
QT_MOC_LITERAL(4, 37, 5), // "event"
QT_MOC_LITERAL(5, 43, 12), // "onMousePress"
QT_MOC_LITERAL(6, 56, 11), // "onItemMoved"
QT_MOC_LITERAL(7, 68, 16), // "QCPAbstractItem*"
QT_MOC_LITERAL(8, 85, 4), // "item"
QT_MOC_LITERAL(9, 90, 6), // "update"
QT_MOC_LITERAL(10, 97, 8), // "LineMode"
QT_MOC_LITERAL(11, 106, 6), // "lmFree"
QT_MOC_LITERAL(12, 113, 14), // "lmFollowCursor"
QT_MOC_LITERAL(13, 128, 9) // "lmTracing"

    },
    "CrossLine\0onMouseMoved\0\0QMouseEvent*\0"
    "event\0onMousePress\0onItemMoved\0"
    "QCPAbstractItem*\0item\0update\0LineMode\0"
    "lmFree\0lmFollowCursor\0lmTracing"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CrossLine[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       1,   46, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       5,    1,   37,    2, 0x0a /* Public */,
       6,    2,   40,    2, 0x0a /* Public */,
       9,    0,   45,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 3,    8,    4,
    QMetaType::Void,

 // enums: name, alias, flags, count, data
      10,   10, 0x0,    3,   51,

 // enum data: key, value
      11, uint(CrossLine::lmFree),
      12, uint(CrossLine::lmFollowCursor),
      13, uint(CrossLine::lmTracing),

       0        // eod
};

void CrossLine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CrossLine *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onMouseMoved((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 1: _t->onMousePress((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 2: _t->onItemMoved((*reinterpret_cast< QCPAbstractItem*(*)>(_a[1])),(*reinterpret_cast< QMouseEvent*(*)>(_a[2]))); break;
        case 3: _t->update(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CrossLine::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CrossLine.data,
    qt_meta_data_CrossLine,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CrossLine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CrossLine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CrossLine.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CrossLine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
