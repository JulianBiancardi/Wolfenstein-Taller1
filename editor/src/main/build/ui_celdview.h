/********************************************************************************
** Form generated from reading UI file 'celdview.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CELDVIEW_H
#define UI_CELDVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CeldView
{
public:
    QFormLayout *formLayout;
    QPushButton *CeldButton;

    void setupUi(QWidget *CeldView)
    {
        if (CeldView->objectName().isEmpty())
            CeldView->setObjectName(QStringLiteral("CeldView"));
        CeldView->resize(100, 100);
        CeldView->setMinimumSize(QSize(100, 100));
        CeldView->setMaximumSize(QSize(100, 100));
        formLayout = new QFormLayout(CeldView);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setHorizontalSpacing(0);
        formLayout->setVerticalSpacing(0);
        formLayout->setContentsMargins(0, 0, 0, 0);
        CeldButton = new QPushButton(CeldView);
        CeldButton->setObjectName(QStringLiteral("CeldButton"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CeldButton->sizePolicy().hasHeightForWidth());
        CeldButton->setSizePolicy(sizePolicy);
        CeldButton->setMinimumSize(QSize(100, 100));
        CeldButton->setMaximumSize(QSize(100, 100));
        CeldButton->setStyleSheet(QLatin1String("QPushButton#CeldButton{\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-color: rgb(104, 112, 121);\n"
"}\n"
"\n"
""));
        CeldButton->setIconSize(QSize(100, 100));

        formLayout->setWidget(0, QFormLayout::FieldRole, CeldButton);


        retranslateUi(CeldView);

        QMetaObject::connectSlotsByName(CeldView);
    } // setupUi

    void retranslateUi(QWidget *CeldView)
    {
        CeldView->setWindowTitle(QApplication::translate("CeldView", "Form", Q_NULLPTR));
        CeldButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CeldView: public Ui_CeldView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CELDVIEW_H
