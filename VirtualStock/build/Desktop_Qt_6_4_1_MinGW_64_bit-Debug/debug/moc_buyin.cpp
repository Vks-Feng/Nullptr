/****************************************************************************
** Meta object code from reading C++ file 'buyin.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../buyin.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'buyin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_buyin_t {
    uint offsetsAndSizes[16];
    char stringdata0[6];
    char stringdata1[23];
    char stringdata2[1];
    char stringdata3[25];
    char stringdata4[31];
    char stringdata5[26];
    char stringdata6[24];
    char stringdata7[27];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_buyin_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_buyin_t qt_meta_stringdata_buyin = {
    {
        QT_MOC_LITERAL(0, 5),  // "buyin"
        QT_MOC_LITERAL(6, 22),  // "on_BuyInButton_clicked"
        QT_MOC_LITERAL(29, 0),  // ""
        QT_MOC_LITERAL(30, 24),  // "on_SellOutButton_clicked"
        QT_MOC_LITERAL(55, 30),  // "on_TradingRecordButton_clicked"
        QT_MOC_LITERAL(86, 25),  // "on_PositionButton_clicked"
        QT_MOC_LITERAL(112, 23),  // "on_IncomeButton_clicked"
        QT_MOC_LITERAL(136, 26)   // "on_RecommendButton_clicked"
    },
    "buyin",
    "on_BuyInButton_clicked",
    "",
    "on_SellOutButton_clicked",
    "on_TradingRecordButton_clicked",
    "on_PositionButton_clicked",
    "on_IncomeButton_clicked",
    "on_RecommendButton_clicked"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_buyin[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x08,    1 /* Private */,
       3,    0,   51,    2, 0x08,    2 /* Private */,
       4,    0,   52,    2, 0x08,    3 /* Private */,
       5,    0,   53,    2, 0x08,    4 /* Private */,
       6,    0,   54,    2, 0x08,    5 /* Private */,
       7,    0,   55,    2, 0x08,    6 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject buyin::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_buyin.offsetsAndSizes,
    qt_meta_data_buyin,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_buyin_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<buyin, std::true_type>,
        // method 'on_BuyInButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_SellOutButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_TradingRecordButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_PositionButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_IncomeButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_RecommendButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void buyin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<buyin *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_BuyInButton_clicked(); break;
        case 1: _t->on_SellOutButton_clicked(); break;
        case 2: _t->on_TradingRecordButton_clicked(); break;
        case 3: _t->on_PositionButton_clicked(); break;
        case 4: _t->on_IncomeButton_clicked(); break;
        case 5: _t->on_RecommendButton_clicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *buyin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *buyin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_buyin.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int buyin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
