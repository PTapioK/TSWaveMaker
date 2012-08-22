/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Mon 20. Aug 22:36:35 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      22,   11,   11,   11, 0x08,
      33,   11,   11,   11, 0x08,
      44,   11,   11,   11, 0x08,
      57,   11,   11,   11, 0x08,
      64,   11,   11,   11, 0x08,
     101,   11,   11,   11, 0x08,
     125,   11,   11,   11, 0x08,
     151,   11,   11,   11, 0x08,
     173,   11,   11,   11, 0x08,
     199,   11,   11,   11, 0x08,
     225,   11,   11,   11, 0x08,
     255,   11,   11,   11, 0x08,
     281,   11,   11,   11, 0x08,
     307,   11,   11,   11, 0x08,
     333,   11,   11,   11, 0x08,
     363,   11,   11,   11, 0x08,
     392,   11,   11,   11, 0x08,
     428,   11,   11,   11, 0x08,
     452,   11,   11,   11, 0x08,
     488,   11,   11,   11, 0x08,
     512,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0NewFile()\0OpenFile()\0"
    "SaveFile()\0SaveFileAs()\0Info()\0"
    "on_listWidget_itemSelectionChanged()\0"
    "on_pushButton_clicked()\0"
    "on_pushButton_2_clicked()\0"
    "on_checkBox_clicked()\0on_pushButton_4_clicked()\0"
    "on_pushButton_3_clicked()\0"
    "on_timeEdit_editingFinished()\0"
    "on_pushButton_5_clicked()\0"
    "on_pushButton_6_clicked()\0"
    "on_pushButton_7_clicked()\0"
    "on_listWidget_2_itemClicked()\0"
    "on_checkBox_5_stateChanged()\0"
    "on_comboBox_2_currentIndexChanged()\0"
    "on_checkBox_2_clicked()\0"
    "on_comboBox_3_currentIndexChanged()\0"
    "on_comboBox_activated()\0"
    "on_checkBox_4_stateChanged()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->NewFile(); break;
        case 1: _t->OpenFile(); break;
        case 2: _t->SaveFile(); break;
        case 3: _t->SaveFileAs(); break;
        case 4: _t->Info(); break;
        case 5: _t->on_listWidget_itemSelectionChanged(); break;
        case 6: _t->on_pushButton_clicked(); break;
        case 7: _t->on_pushButton_2_clicked(); break;
        case 8: _t->on_checkBox_clicked(); break;
        case 9: _t->on_pushButton_4_clicked(); break;
        case 10: _t->on_pushButton_3_clicked(); break;
        case 11: _t->on_timeEdit_editingFinished(); break;
        case 12: _t->on_pushButton_5_clicked(); break;
        case 13: _t->on_pushButton_6_clicked(); break;
        case 14: _t->on_pushButton_7_clicked(); break;
        case 15: _t->on_listWidget_2_itemClicked(); break;
        case 16: _t->on_checkBox_5_stateChanged(); break;
        case 17: _t->on_comboBox_2_currentIndexChanged(); break;
        case 18: _t->on_checkBox_2_clicked(); break;
        case 19: _t->on_comboBox_3_currentIndexChanged(); break;
        case 20: _t->on_comboBox_activated(); break;
        case 21: _t->on_checkBox_4_stateChanged(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
