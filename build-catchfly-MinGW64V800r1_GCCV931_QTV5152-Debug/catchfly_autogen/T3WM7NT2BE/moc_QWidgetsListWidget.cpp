/****************************************************************************
** Meta object code from reading C++ file 'QWidgetsListWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../catchfly/ListWW/QWidgetsListWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QWidgetsListWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QWidgetsListWidget_t {
    QByteArrayData data[17];
    char stringdata0[201];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QWidgetsListWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QWidgetsListWidget_t qt_meta_stringdata_QWidgetsListWidget = {
    {
QT_MOC_LITERAL(0, 0, 18), // "QWidgetsListWidget"
QT_MOC_LITERAL(1, 19, 12), // "rowsInserted"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 11), // "QModelIndex"
QT_MOC_LITERAL(4, 45, 6), // "parent"
QT_MOC_LITERAL(5, 52, 5), // "start"
QT_MOC_LITERAL(6, 58, 3), // "end"
QT_MOC_LITERAL(7, 62, 20), // "rowsAboutToBeRemoved"
QT_MOC_LITERAL(8, 83, 11), // "dataChanged"
QT_MOC_LITERAL(9, 95, 7), // "topLeft"
QT_MOC_LITERAL(10, 103, 11), // "bottomRight"
QT_MOC_LITERAL(11, 115, 12), // "QVector<int>"
QT_MOC_LITERAL(12, 128, 5), // "roles"
QT_MOC_LITERAL(13, 134, 13), // "createDisplay"
QT_MOC_LITERAL(14, 148, 26), // "QWidgetsListWidgetDisplay*"
QT_MOC_LITERAL(15, 175, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(16, 192, 8) // "listItem"

    },
    "QWidgetsListWidget\0rowsInserted\0\0"
    "QModelIndex\0parent\0start\0end\0"
    "rowsAboutToBeRemoved\0dataChanged\0"
    "topLeft\0bottomRight\0QVector<int>\0roles\0"
    "createDisplay\0QWidgetsListWidgetDisplay*\0"
    "QListWidgetItem*\0listItem"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QWidgetsListWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   34,    2, 0x09 /* Protected */,
       7,    3,   41,    2, 0x09 /* Protected */,
       8,    3,   48,    2, 0x09 /* Protected */,
      13,    1,   55,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,    4,    5,    6,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,    4,    5,    6,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 11,    9,   10,   12,
    0x80000000 | 14, 0x80000000 | 15,   16,

       0        // eod
};

void QWidgetsListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QWidgetsListWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->rowsInserted((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->rowsAboutToBeRemoved((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->dataChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])),(*reinterpret_cast< const QVector<int>(*)>(_a[3]))); break;
        case 3: { QWidgetsListWidgetDisplay* _r = _t->createDisplay((*reinterpret_cast< QListWidgetItem*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QWidgetsListWidgetDisplay**>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QWidgetsListWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QListWidget::staticMetaObject>(),
    qt_meta_stringdata_QWidgetsListWidget.data,
    qt_meta_data_QWidgetsListWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QWidgetsListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QWidgetsListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QWidgetsListWidget.stringdata0))
        return static_cast<void*>(this);
    return QListWidget::qt_metacast(_clname);
}

int QWidgetsListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
