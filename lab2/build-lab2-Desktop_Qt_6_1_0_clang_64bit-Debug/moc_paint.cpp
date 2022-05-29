/****************************************************************************
** Meta object code from reading C++ file 'paint.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../lab2/paint.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'paint.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Paint_t {
    const uint offsetsAndSize[40];
    char stringdata0[347];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_Paint_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_Paint_t qt_meta_stringdata_Paint = {
    {
QT_MOC_LITERAL(0, 5), // "Paint"
QT_MOC_LITERAL(6, 9), // "slotTimer"
QT_MOC_LITERAL(16, 0), // ""
QT_MOC_LITERAL(17, 20), // "on_rectangle_clicked"
QT_MOC_LITERAL(38, 18), // "on_ellipse_clicked"
QT_MOC_LITERAL(57, 15), // "on_line_clicked"
QT_MOC_LITERAL(73, 22), // "on_broken_line_clicked"
QT_MOC_LITERAL(96, 15), // "on_draw_clicked"
QT_MOC_LITERAL(112, 15), // "on_move_clicked"
QT_MOC_LITERAL(128, 28), // "on_scale_slider_valueChanged"
QT_MOC_LITERAL(157, 5), // "value"
QT_MOC_LITERAL(163, 29), // "on_rotate_slider_valueChanged"
QT_MOC_LITERAL(193, 29), // "on_width_edit_editingFinished"
QT_MOC_LITERAL(223, 15), // "on_undo_clicked"
QT_MOC_LITERAL(239, 15), // "on_redo_clicked"
QT_MOC_LITERAL(255, 17), // "on_colour_clicked"
QT_MOC_LITERAL(273, 21), // "on_fill_color_clicked"
QT_MOC_LITERAL(295, 18), // "on_polygon_clicked"
QT_MOC_LITERAL(314, 16), // "on_clear_clicked"
QT_MOC_LITERAL(331, 15) // "on_copy_clicked"

    },
    "Paint\0slotTimer\0\0on_rectangle_clicked\0"
    "on_ellipse_clicked\0on_line_clicked\0"
    "on_broken_line_clicked\0on_draw_clicked\0"
    "on_move_clicked\0on_scale_slider_valueChanged\0"
    "value\0on_rotate_slider_valueChanged\0"
    "on_width_edit_editingFinished\0"
    "on_undo_clicked\0on_redo_clicked\0"
    "on_colour_clicked\0on_fill_color_clicked\0"
    "on_polygon_clicked\0on_clear_clicked\0"
    "on_copy_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Paint[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  116,    2, 0x08,    0 /* Private */,
       3,    0,  117,    2, 0x08,    1 /* Private */,
       4,    0,  118,    2, 0x08,    2 /* Private */,
       5,    0,  119,    2, 0x08,    3 /* Private */,
       6,    0,  120,    2, 0x08,    4 /* Private */,
       7,    0,  121,    2, 0x08,    5 /* Private */,
       8,    0,  122,    2, 0x08,    6 /* Private */,
       9,    1,  123,    2, 0x08,    7 /* Private */,
      11,    1,  126,    2, 0x08,    9 /* Private */,
      12,    0,  129,    2, 0x08,   11 /* Private */,
      13,    0,  130,    2, 0x08,   12 /* Private */,
      14,    0,  131,    2, 0x08,   13 /* Private */,
      15,    0,  132,    2, 0x08,   14 /* Private */,
      16,    0,  133,    2, 0x08,   15 /* Private */,
      17,    0,  134,    2, 0x08,   16 /* Private */,
      18,    0,  135,    2, 0x08,   17 /* Private */,
      19,    0,  136,    2, 0x08,   18 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Paint::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Paint *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->slotTimer(); break;
        case 1: _t->on_rectangle_clicked(); break;
        case 2: _t->on_ellipse_clicked(); break;
        case 3: _t->on_line_clicked(); break;
        case 4: _t->on_broken_line_clicked(); break;
        case 5: _t->on_draw_clicked(); break;
        case 6: _t->on_move_clicked(); break;
        case 7: _t->on_scale_slider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_rotate_slider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_width_edit_editingFinished(); break;
        case 10: _t->on_undo_clicked(); break;
        case 11: _t->on_redo_clicked(); break;
        case 12: _t->on_colour_clicked(); break;
        case 13: _t->on_fill_color_clicked(); break;
        case 14: _t->on_polygon_clicked(); break;
        case 15: _t->on_clear_clicked(); break;
        case 16: _t->on_copy_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject Paint::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Paint.offsetsAndSize,
    qt_meta_data_Paint,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Paint_t

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *Paint::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Paint::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Paint.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Paint::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 17;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
