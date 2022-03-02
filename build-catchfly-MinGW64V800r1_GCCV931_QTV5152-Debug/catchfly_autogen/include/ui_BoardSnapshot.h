/********************************************************************************
** Form generated from reading UI file 'boardsnapshot.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOARDSNAPSHOT_H
#define UI_BOARDSNAPSHOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BoardSnapshot
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *onewdt;

    void setupUi(QWidget *BoardSnapshot)
    {
        if (BoardSnapshot->objectName().isEmpty())
            BoardSnapshot->setObjectName(QString::fromUtf8("BoardSnapshot"));
        BoardSnapshot->resize(1222, 789);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(BoardSnapshot->sizePolicy().hasHeightForWidth());
        BoardSnapshot->setSizePolicy(sizePolicy);
        BoardSnapshot->setMinimumSize(QSize(1222, 444));
        verticalLayout = new QVBoxLayout(BoardSnapshot);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        onewdt = new QWidget(BoardSnapshot);
        onewdt->setObjectName(QString::fromUtf8("onewdt"));
        onewdt->setEnabled(true);
        sizePolicy.setHeightForWidth(onewdt->sizePolicy().hasHeightForWidth());
        onewdt->setSizePolicy(sizePolicy);
        onewdt->setMinimumSize(QSize(1111, 333));
        onewdt->setStyleSheet(QString::fromUtf8("QWidget#onewdt{background-color: rgb(111, 222,1);border: 2px solid rgb(255, 0, 127);}"));

        verticalLayout->addWidget(onewdt);


        retranslateUi(BoardSnapshot);

        QMetaObject::connectSlotsByName(BoardSnapshot);
    } // setupUi

    void retranslateUi(QWidget *BoardSnapshot)
    {
        BoardSnapshot->setWindowTitle(QCoreApplication::translate("BoardSnapshot", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BoardSnapshot: public Ui_BoardSnapshot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOARDSNAPSHOT_H
