/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionstart_1;
    QAction *actionstop_1;
    QAction *actionstart_2;
    QAction *actionstop_2;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menutest;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionstart_1 = new QAction(MainWindow);
        actionstart_1->setObjectName(QString::fromUtf8("actionstart_1"));
        actionstop_1 = new QAction(MainWindow);
        actionstop_1->setObjectName(QString::fromUtf8("actionstop_1"));
        actionstart_2 = new QAction(MainWindow);
        actionstart_2->setObjectName(QString::fromUtf8("actionstart_2"));
        actionstop_2 = new QAction(MainWindow);
        actionstop_2->setObjectName(QString::fromUtf8("actionstop_2"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menutest = new QMenu(menubar);
        menutest->setObjectName(QString::fromUtf8("menutest"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menutest->menuAction());
        menutest->addAction(actionstart_1);
        toolBar->addAction(actionstart_1);
        toolBar->addAction(actionstop_1);
        toolBar->addAction(actionstart_2);
        toolBar->addAction(actionstop_2);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionstart_1->setText(QCoreApplication::translate("MainWindow", "start_1", nullptr));
#if QT_CONFIG(tooltip)
        actionstart_1->setToolTip(QCoreApplication::translate("MainWindow", "start_1", nullptr));
#endif // QT_CONFIG(tooltip)
        actionstop_1->setText(QCoreApplication::translate("MainWindow", "stop_1", nullptr));
#if QT_CONFIG(tooltip)
        actionstop_1->setToolTip(QCoreApplication::translate("MainWindow", "stop_1", nullptr));
#endif // QT_CONFIG(tooltip)
        actionstart_2->setText(QCoreApplication::translate("MainWindow", "start_2", nullptr));
#if QT_CONFIG(tooltip)
        actionstart_2->setToolTip(QCoreApplication::translate("MainWindow", "start_2", nullptr));
#endif // QT_CONFIG(tooltip)
        actionstop_2->setText(QCoreApplication::translate("MainWindow", "stop_2", nullptr));
#if QT_CONFIG(tooltip)
        actionstop_2->setToolTip(QCoreApplication::translate("MainWindow", "stop_2", nullptr));
#endif // QT_CONFIG(tooltip)
        menutest->setTitle(QCoreApplication::translate("MainWindow", "test", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
