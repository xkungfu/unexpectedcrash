/****************************************************************************
** Meta object code from reading C++ file 'candlecontainer_list.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../catchfly/CandleList/container/candlecontainer_list.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'candlecontainer_list.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CandleContainer_List_t {
    QByteArrayData data[10];
    char stringdata0[142];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CandleContainer_List_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CandleContainer_List_t qt_meta_stringdata_CandleContainer_List = {
    {
QT_MOC_LITERAL(0, 0, 20), // "CandleContainer_List"
QT_MOC_LITERAL(1, 21, 16), // "showpopup_ATLIST"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 9), // "candleobj"
QT_MOC_LITERAL(4, 49, 12), // "reload_popup"
QT_MOC_LITERAL(5, 62, 13), // "createDisplay"
QT_MOC_LITERAL(6, 76, 26), // "QWidgetsListWidgetDisplay*"
QT_MOC_LITERAL(7, 103, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(8, 120, 8), // "listItem"
QT_MOC_LITERAL(9, 129, 12) // "delete_popup"

    },
    "CandleContainer_List\0showpopup_ATLIST\0"
    "\0candleobj\0reload_popup\0createDisplay\0"
    "QWidgetsListWidgetDisplay*\0QListWidgetItem*\0"
    "listItem\0delete_popup"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CandleContainer_List[] = {

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
       1,    1,   34,    2, 0x0a /* Public */,
       4,    0,   37,    2, 0x0a /* Public */,
       5,    1,   38,    2, 0x09 /* Protected */,
       9,    0,   41,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::QObjectStar,    3,
    QMetaType::Void,
    0x80000000 | 6, 0x80000000 | 7,    8,
    QMetaType::Void,

       0        // eod
};

void CandleContainer_List::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CandleContainer_List *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showpopup_ATLIST((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 1: _t->reload_popup(); break;
        case 2: { QWidgetsListWidgetDisplay* _r = _t->createDisplay((*reinterpret_cast< QListWidgetItem*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QWidgetsListWidgetDisplay**>(_a[0]) = std::move(_r); }  break;
        case 3: _t->delete_popup(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CandleContainer_List::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidgetsListWidget::staticMetaObject>(),
    qt_meta_stringdata_CandleContainer_List.data,
    qt_meta_data_CandleContainer_List,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CandleContainer_List::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CandleContainer_List::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CandleContainer_List.stringdata0))
        return static_cast<void*>(this);
    return QWidgetsListWidget::qt_metacast(_clname);
}

int CandleContainer_List::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidgetsListWidget::qt_metacall(_c, _id, _a);
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
