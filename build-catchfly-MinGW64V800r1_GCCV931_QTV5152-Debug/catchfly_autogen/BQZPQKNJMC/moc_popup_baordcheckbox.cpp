/****************************************************************************
** Meta object code from reading C++ file 'popup_baordcheckbox.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../catchfly/Popup/popup_baordcheckbox.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'popup_baordcheckbox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PopupBoardCheckbox_t {
    QByteArrayData data[6];
    char stringdata0[124];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PopupBoardCheckbox_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PopupBoardCheckbox_t qt_meta_stringdata_PopupBoardCheckbox = {
    {
QT_MOC_LITERAL(0, 0, 18), // "PopupBoardCheckbox"
QT_MOC_LITERAL(1, 19, 27), // "send_FAVPOPUPITEM_FROMPOPUP"
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 8), // "filename"
QT_MOC_LITERAL(4, 57, 45), // "send_change_fav_finished_ATPo..."
QT_MOC_LITERAL(5, 103, 20) // "onBoardButtonClicked"

    },
    "PopupBoardCheckbox\0send_FAVPOPUPITEM_FROMPOPUP\0"
    "\0filename\0send_change_fav_finished_ATPopupBoardCheckbox\0"
    "onBoardButtonClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PopupBoardCheckbox[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    0,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   33,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void PopupBoardCheckbox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PopupBoardCheckbox *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send_FAVPOPUPITEM_FROMPOPUP((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->send_change_fav_finished_ATPopupBoardCheckbox(); break;
        case 2: _t->onBoardButtonClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PopupBoardCheckbox::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PopupBoardCheckbox::send_FAVPOPUPITEM_FROMPOPUP)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PopupBoardCheckbox::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PopupBoardCheckbox::send_change_fav_finished_ATPopupBoardCheckbox)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PopupBoardCheckbox::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_PopupBoardCheckbox.data,
    qt_meta_data_PopupBoardCheckbox,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PopupBoardCheckbox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PopupBoardCheckbox::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PopupBoardCheckbox.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PopupBoardCheckbox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void PopupBoardCheckbox::send_FAVPOPUPITEM_FROMPOPUP(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PopupBoardCheckbox::send_change_fav_finished_ATPopupBoardCheckbox()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
