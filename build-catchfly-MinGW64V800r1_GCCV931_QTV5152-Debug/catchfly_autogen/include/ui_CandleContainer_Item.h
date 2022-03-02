/********************************************************************************
** Form generated from reading UI file 'CandleContainer_Item.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CANDLECONTAINER_ITEM_H
#define UI_CANDLECONTAINER_ITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CandleContainer_Item
{
public:
    QGridLayout *gridLayout;
    QWidget *onewdt;

    void setupUi(QWidget *CandleContainer_Item)
    {
        if (CandleContainer_Item->objectName().isEmpty())
            CandleContainer_Item->setObjectName(QString::fromUtf8("CandleContainer_Item"));
        CandleContainer_Item->resize(924, 568);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CandleContainer_Item->sizePolicy().hasHeightForWidth());
        CandleContainer_Item->setSizePolicy(sizePolicy);
        CandleContainer_Item->setStyleSheet(QString::fromUtf8("QWidget#Display{background-color: rgb(177, 111, 1);border: 2px solid rgb(255, 0, 127);}\n"
""));
        gridLayout = new QGridLayout(CandleContainer_Item);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        onewdt = new QWidget(CandleContainer_Item);
        onewdt->setObjectName(QString::fromUtf8("onewdt"));
        sizePolicy.setHeightForWidth(onewdt->sizePolicy().hasHeightForWidth());
        onewdt->setSizePolicy(sizePolicy);
        onewdt->setMaximumSize(QSize(16777215, 16777215));
        onewdt->setStyleSheet(QString::fromUtf8("QWidget#plotcontainer{background-color: rgb(111, 222,1);border: 2px solid rgb(255, 0, 127);}\n"
"QWidget#timeline_wrapper{background-color: rgb(77, 55,33);border: 2px solid rgb(255, 0, 127);}\n"
""));

        gridLayout->addWidget(onewdt, 0, 0, 1, 1);


        retranslateUi(CandleContainer_Item);

        QMetaObject::connectSlotsByName(CandleContainer_Item);
    } // setupUi

    void retranslateUi(QWidget *CandleContainer_Item)
    {
        CandleContainer_Item->setWindowTitle(QCoreApplication::translate("CandleContainer_Item", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CandleContainer_Item: public Ui_CandleContainer_Item {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANDLECONTAINER_ITEM_H
