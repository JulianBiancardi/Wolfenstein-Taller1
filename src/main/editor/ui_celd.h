/********************************************************************************
** Form generated from reading UI file 'celd.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CELD_H
#define UI_CELD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Celd
{
public:
    QFormLayout *formLayout;
    QPushButton *CeldButton;

    void setupUi(QWidget *Celd)
    {
        if (Celd->objectName().isEmpty())
            Celd->setObjectName(QStringLiteral("Celd"));
        Celd->resize(100, 100);
        Celd->setMinimumSize(QSize(100, 100));
        Celd->setMaximumSize(QSize(100, 100));
        formLayout = new QFormLayout(Celd);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setHorizontalSpacing(0);
        formLayout->setVerticalSpacing(0);
        formLayout->setContentsMargins(0, 0, 0, 0);
        CeldButton = new QPushButton(Celd);
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


        retranslateUi(Celd);

        QMetaObject::connectSlotsByName(Celd);
    } // setupUi

    void retranslateUi(QWidget *Celd)
    {
        Celd->setWindowTitle(QApplication::translate("Celd", "Form", Q_NULLPTR));
        CeldButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Celd: public Ui_Celd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CELD_H
