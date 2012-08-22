/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed 22. Aug 17:03:57 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDockWidget>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTimeEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew_file;
    QAction *actionOpen_file;
    QAction *actionSave_file;
    QAction *actionQuit;
    QAction *actionSave_As;
    QAction *actionInfo;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QStatusBar *statusBar;
    QDockWidget *dockWidget_4;
    QWidget *dockWidgetContents_4;
    QListWidget *listWidget;
    QLabel *label_2;
    QCheckBox *checkBox;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_4;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLabel *label_3;
    QTimeEdit *timeEdit;
    QLabel *label_8;
    QListWidget *listWidget_2;
    QLabel *label_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QCheckBox *checkBox_5;
    QLabel *label_5;
    QComboBox *comboBox_2;
    QCheckBox *checkBox_2;
    QLabel *label_6;
    QComboBox *comboBox_3;
    QLabel *label_7;
    QComboBox *comboBox;
    QCheckBox *checkBox_4;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1024, 768);
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        actionNew_file = new QAction(MainWindow);
        actionNew_file->setObjectName(QString::fromUtf8("actionNew_file"));
        actionOpen_file = new QAction(MainWindow);
        actionOpen_file->setObjectName(QString::fromUtf8("actionOpen_file"));
        actionSave_file = new QAction(MainWindow);
        actionSave_file->setObjectName(QString::fromUtf8("actionSave_file"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QString::fromUtf8("actionSave_As"));
        actionInfo = new QAction(MainWindow);
        actionInfo->setObjectName(QString::fromUtf8("actionInfo"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        dockWidget_4 = new QDockWidget(MainWindow);
        dockWidget_4->setObjectName(QString::fromUtf8("dockWidget_4"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dockWidget_4->sizePolicy().hasHeightForWidth());
        dockWidget_4->setSizePolicy(sizePolicy);
        dockWidget_4->setMinimumSize(QSize(700, 300));
        dockWidget_4->setMaximumSize(QSize(700, 300));
        dockWidget_4->setFloating(true);
        dockWidgetContents_4 = new QWidget();
        dockWidgetContents_4->setObjectName(QString::fromUtf8("dockWidgetContents_4"));
        listWidget = new QListWidget(dockWidgetContents_4);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(10, 30, 111, 211));
        label_2 = new QLabel(dockWidgetContents_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 10, 61, 16));
        checkBox = new QCheckBox(dockWidgetContents_4);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(30, 250, 70, 17));
        label = new QLabel(dockWidgetContents_4);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(170, 10, 46, 16));
        lineEdit = new QLineEdit(dockWidgetContents_4);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(130, 30, 113, 20));
        pushButton = new QPushButton(dockWidgetContents_4);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(150, 60, 75, 23));
        pushButton_4 = new QPushButton(dockWidgetContents_4);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(150, 90, 75, 23));
        pushButton_2 = new QPushButton(dockWidgetContents_4);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(150, 120, 75, 23));
        pushButton_3 = new QPushButton(dockWidgetContents_4);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(150, 150, 75, 23));
        label_3 = new QLabel(dockWidgetContents_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(140, 190, 101, 31));
        label_3->setWordWrap(false);
        timeEdit = new QTimeEdit(dockWidgetContents_4);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        timeEdit->setGeometry(QRect(130, 220, 118, 22));
        label_8 = new QLabel(dockWidgetContents_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(160, 250, 46, 13));
        listWidget_2 = new QListWidget(dockWidgetContents_4);
        listWidget_2->setObjectName(QString::fromUtf8("listWidget_2"));
        listWidget_2->setGeometry(QRect(260, 30, 111, 231));
        label_4 = new QLabel(dockWidgetContents_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(290, 10, 46, 16));
        pushButton_5 = new QPushButton(dockWidgetContents_4);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(400, 30, 75, 23));
        pushButton_6 = new QPushButton(dockWidgetContents_4);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(400, 60, 75, 23));
        pushButton_7 = new QPushButton(dockWidgetContents_4);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(400, 90, 75, 23));
        checkBox_5 = new QCheckBox(dockWidgetContents_4);
        checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));
        checkBox_5->setGeometry(QRect(390, 120, 101, 17));
        label_5 = new QLabel(dockWidgetContents_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(390, 150, 46, 13));
        comboBox_2 = new QComboBox(dockWidgetContents_4);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(440, 150, 41, 20));
        comboBox_2->setMaximumSize(QSize(41, 16777215));
        comboBox_2->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        comboBox_2->setInputMethodHints(Qt::ImhPreferNumbers);
        comboBox_2->setEditable(true);
        comboBox_2->setMaxCount(99);
        comboBox_2->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);
        checkBox_2 = new QCheckBox(dockWidgetContents_4);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setEnabled(true);
        checkBox_2->setGeometry(QRect(390, 180, 281, 21));
        checkBox_2->setAutoFillBackground(false);
        checkBox_2->setCheckable(true);
        checkBox_2->setChecked(false);
        checkBox_2->setAutoExclusive(false);
        checkBox_2->setTristate(false);
        label_6 = new QLabel(dockWidgetContents_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(390, 210, 91, 16));
        comboBox_3 = new QComboBox(dockWidgetContents_4);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setEnabled(false);
        comboBox_3->setGeometry(QRect(490, 210, 41, 22));
        comboBox_3->setInputMethodHints(Qt::ImhPreferNumbers);
        comboBox_3->setEditable(false);
        comboBox_3->setMaxCount(99);
        label_7 = new QLabel(dockWidgetContents_4);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(540, 10, 61, 16));
        comboBox = new QComboBox(dockWidgetContents_4);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setEnabled(false);
        comboBox->setGeometry(QRect(500, 30, 121, 21));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy1);
        comboBox->setInputMethodHints(Qt::ImhNone);
        comboBox->setEditable(false);
        comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);
        comboBox->setFrame(true);
        checkBox_4 = new QCheckBox(dockWidgetContents_4);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setEnabled(false);
        checkBox_4->setGeometry(QRect(500, 60, 131, 17));
        dockWidget_4->setWidget(dockWidgetContents_4);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget_4);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew_file);
        menuFile->addAction(actionOpen_file);
        menuFile->addAction(actionSave_file);
        menuFile->addAction(actionSave_As);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuHelp->addAction(actionInfo);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "TSWaveMaker Trigger TechDemo", 0, QApplication::UnicodeUTF8));
        actionNew_file->setText(QApplication::translate("MainWindow", "New file", 0, QApplication::UnicodeUTF8));
        actionOpen_file->setText(QApplication::translate("MainWindow", "Open file", 0, QApplication::UnicodeUTF8));
        actionSave_file->setText(QApplication::translate("MainWindow", "Save file", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
        actionSave_As->setText(QApplication::translate("MainWindow", "Save file as", 0, QApplication::UnicodeUTF8));
        actionInfo->setText(QApplication::translate("MainWindow", "Info", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
        dockWidget_4->setWindowTitle(QApplication::translate("MainWindow", "Trigger Section", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Trigger list", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("MainWindow", "Disabled", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Name", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "New", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("MainWindow", "Delete", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("MainWindow", "Edit name", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("MainWindow", "Clone", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Time after last action", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "Not set", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Action list", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("MainWindow", "New", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QApplication::translate("MainWindow", "Delete", 0, QApplication::UnicodeUTF8));
        pushButton_7->setText(QApplication::translate("MainWindow", "Clone", 0, QApplication::UnicodeUTF8));
        checkBox_5->setText(QApplication::translate("MainWindow", "Reinforcement", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Waypoint", 0, QApplication::UnicodeUTF8));
        checkBox_2->setText(QApplication::translate("MainWindow", "Make waypoints grow in ascending order to all actions", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "Starting waypoint", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "Teamtype", 0, QApplication::UnicodeUTF8));
        checkBox_4->setText(QApplication::translate("MainWindow", "Same to all actions", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
