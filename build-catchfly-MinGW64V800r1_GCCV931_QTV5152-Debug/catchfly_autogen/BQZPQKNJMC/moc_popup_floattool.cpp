/****************************************************************************
** Meta object code from reading C++ file 'popup_floattool.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../catchfly/Popup/popup_floattool.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'popup_floattool.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PopupFloatTool_t {
    QByteArrayData data[8];
    char stringdata0[143];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PopupFloatTool_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PopupFloatTool_t qt_meta_stringdata_PopupFloatTool = {
    {
QT_MOC_LITERAL(0, 0, 14), // "PopupFloatTool"
QT_MOC_LITERAL(1, 15, 27), // "send_FAVPOPUPITEM_FROMPOPUP"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 8), // "filename"
QT_MOC_LITERAL(4, 53, 41), // "send_change_fav_finished_ATPo..."
QT_MOC_LITERAL(5, 95, 11), // "change_mask"
QT_MOC_LITERAL(6, 107, 5), // "value"
QT_MOC_LITERAL(7, 113, 29) // "at_qcpplot_mask_x_btn_clicked"

    },
    "PopupFloatTool\0send_FAVPOPUPITEM_FROMPOPUP\0"
    "\0filename\0send_change_fav_finished_ATPopupFloatTool\0"
    "change_mask\0value\0at_qcpplot_mask_x_btn_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PopupFloatTool[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    0,   37,    2, 0x06 /* Public */,
       5,    1,   38,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   41,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void PopupFloatTool::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PopupFloatTool *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send_FAVPOPUPITEM_FROMPOPUP((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->send_change_fav_finished_ATPopupFloatTool(); break;
        case 2: _t->change_mask((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->at_qcpplot_mask_x_btn_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PopupFloatTool::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PopupFloatTool::send_FAVPOPUPITEM_FROMPOPUP)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PopupFloatTool::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PopupFloatTool::send_change_fav_finished_ATPopupFloatTool)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PopupFloatTool::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PopupFloatTool::change_mask)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PopupFloatTool::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_PopupFloatTool.data,
    qt_meta_data_PopupFloatTool,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PopupFloatTool::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PopupFloatTool::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PopupFloatTool.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PopupFloatTool::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void PopupFloatTool::send_FAVPOPUPITEM_FROMPOPUP(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PopupFloatTool::send_change_fav_finished_ATPopupFloatTool()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void PopupFloatTool::change_mask(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
