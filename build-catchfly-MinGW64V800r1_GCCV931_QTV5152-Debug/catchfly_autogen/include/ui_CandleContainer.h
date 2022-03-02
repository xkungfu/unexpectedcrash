/********************************************************************************
** Form generated from reading UI file 'CandleContainer.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CANDLECONTAINER_H
#define UI_CANDLECONTAINER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CandleContainer
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *mainwdt;

    void setupUi(QWidget *CandleContainer)
    {
        if (CandleContainer->objectName().isEmpty())
            CandleContainer->setObjectName(QString::fromUtf8("CandleContainer"));
        CandleContainer->resize(1017, 718);
        verticalLayout = new QVBoxLayout(CandleContainer);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        mainwdt = new QWidget(CandleContainer);
        mainwdt->setObjectName(QString::fromUtf8("mainwdt"));
        mainwdt->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 147, 255);"));

        verticalLayout->addWidget(mainwdt);


        retranslateUi(CandleContainer);

        QMetaObject::connectSlotsByName(CandleContainer);
    } // setupUi

    void retranslateUi(QWidget *CandleContainer)
    {
        CandleContainer->setWindowTitle(QCoreApplication::translate("CandleContainer", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CandleContainer: public Ui_CandleContainer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANDLECONTAINER_H
