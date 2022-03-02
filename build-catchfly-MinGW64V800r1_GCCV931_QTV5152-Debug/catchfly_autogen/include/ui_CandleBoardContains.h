/********************************************************************************
** Form generated from reading UI file 'CandleBoardContains.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CANDLEBOARDCONTAINS_H
#define UI_CANDLEBOARDCONTAINS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CandleBoardContains
{
public:
    QGridLayout *gridLayout;
    QWidget *toolpanelwdt;
    QWidget *boardlistwdt;
    QWidget *onewdt;

    void setupUi(QWidget *CandleBoardContains)
    {
        if (CandleBoardContains->objectName().isEmpty())
            CandleBoardContains->setObjectName(QString::fromUtf8("CandleBoardContains"));
        CandleBoardContains->resize(1007, 658);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CandleBoardContains->sizePolicy().hasHeightForWidth());
        CandleBoardContains->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(CandleBoardContains);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        toolpanelwdt = new QWidget(CandleBoardContains);
        toolpanelwdt->setObjectName(QString::fromUtf8("toolpanelwdt"));
        toolpanelwdt->setStyleSheet(QString::fromUtf8("QWidget#toolpanelwdt{background-color: rgb(222, 222, 222);border: 2px solid rgb(222, 222, 222);}\n"
""));

        gridLayout->addWidget(toolpanelwdt, 0, 2, 1, 1);

        boardlistwdt = new QWidget(CandleBoardContains);
        boardlistwdt->setObjectName(QString::fromUtf8("boardlistwdt"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(boardlistwdt->sizePolicy().hasHeightForWidth());
        boardlistwdt->setSizePolicy(sizePolicy1);
        boardlistwdt->setStyleSheet(QString::fromUtf8("QWidget#boardlistwdt{background-color: rgb(222, 222, 222);border: 2px solid rgb(222, 222, 222);}\n"
""));

        gridLayout->addWidget(boardlistwdt, 0, 1, 1, 1);

        onewdt = new QWidget(CandleBoardContains);
        onewdt->setObjectName(QString::fromUtf8("onewdt"));
        sizePolicy.setHeightForWidth(onewdt->sizePolicy().hasHeightForWidth());
        onewdt->setSizePolicy(sizePolicy);
        onewdt->setStyleSheet(QString::fromUtf8("background-color: rgb(190, 255, 208);"));

        gridLayout->addWidget(onewdt, 1, 1, 1, 2);


        retranslateUi(CandleBoardContains);

        QMetaObject::connectSlotsByName(CandleBoardContains);
    } // setupUi

    void retranslateUi(QWidget *CandleBoardContains)
    {
        CandleBoardContains->setWindowTitle(QCoreApplication::translate("CandleBoardContains", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CandleBoardContains: public Ui_CandleBoardContains {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANDLEBOARDCONTAINS_H
