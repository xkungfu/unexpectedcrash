/********************************************************************************
** Form generated from reading UI file 'CandleContainerSingle.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CANDLECONTAINERSINGLE_H
#define UI_CANDLECONTAINERSINGLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CandleContainerSingle
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *onewdt;

    void setupUi(QWidget *CandleContainerSingle)
    {
        if (CandleContainerSingle->objectName().isEmpty())
            CandleContainerSingle->setObjectName(QString::fromUtf8("CandleContainerSingle"));
        CandleContainerSingle->resize(1222, 789);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CandleContainerSingle->sizePolicy().hasHeightForWidth());
        CandleContainerSingle->setSizePolicy(sizePolicy);
        CandleContainerSingle->setMinimumSize(QSize(1222, 444));
        verticalLayout = new QVBoxLayout(CandleContainerSingle);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        onewdt = new QWidget(CandleContainerSingle);
        onewdt->setObjectName(QString::fromUtf8("onewdt"));
        onewdt->setEnabled(true);
        sizePolicy.setHeightForWidth(onewdt->sizePolicy().hasHeightForWidth());
        onewdt->setSizePolicy(sizePolicy);
        onewdt->setMinimumSize(QSize(1111, 333));
        onewdt->setStyleSheet(QString::fromUtf8("QWidget#onewdt{background-color: rgb(111, 222,1);border: 2px solid rgb(255, 0, 127);}"));

        verticalLayout->addWidget(onewdt);


        retranslateUi(CandleContainerSingle);

        QMetaObject::connectSlotsByName(CandleContainerSingle);
    } // setupUi

    void retranslateUi(QWidget *CandleContainerSingle)
    {
        CandleContainerSingle->setWindowTitle(QCoreApplication::translate("CandleContainerSingle", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CandleContainerSingle: public Ui_CandleContainerSingle {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANDLECONTAINERSINGLE_H
