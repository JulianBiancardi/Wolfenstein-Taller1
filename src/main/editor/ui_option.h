/********************************************************************************
** Form generated from reading UI file 'option.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTION_H
#define UI_OPTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Option
{
public:
    QFormLayout *formLayout;
    QPushButton *OptionButton;

    void setupUi(QWidget *Option)
    {
        if (Option->objectName().isEmpty())
            Option->setObjectName(QStringLiteral("Option"));
        Option->setEnabled(true);
        Option->resize(100, 100);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Option->sizePolicy().hasHeightForWidth());
        Option->setSizePolicy(sizePolicy);
        Option->setMinimumSize(QSize(100, 100));
        Option->setMaximumSize(QSize(100, 100));
        Option->setBaseSize(QSize(100, 100));
        Option->setLayoutDirection(Qt::LeftToRight);
        formLayout = new QFormLayout(Option);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setHorizontalSpacing(0);
        formLayout->setVerticalSpacing(0);
        formLayout->setContentsMargins(0, 0, 0, 0);
        OptionButton = new QPushButton(Option);
        OptionButton->setObjectName(QStringLiteral("OptionButton"));
        OptionButton->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(OptionButton->sizePolicy().hasHeightForWidth());
        OptionButton->setSizePolicy(sizePolicy1);
        OptionButton->setMinimumSize(QSize(100, 100));
        OptionButton->setStyleSheet(QLatin1String("QPushButton#OptionButton{\n"
"	background-color: rgb(170, 170, 170);\n"
"	border-style: outset;\n"
"	border-width: 2px;\n"
"	border-radius: 10px;\n"
"	border-color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QPushButton#OptionButton:hover {\n"
"	background-color: rgb(140, 140, 140);\n"
"}\n"
"\n"
"QPushButton#OptionButton:checked {\n"
"	background-color: rgb(100, 100, 100);\n"
"	color: rgb(255, 255, 0);\n"
"}\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
""));
        OptionButton->setIconSize(QSize(80, 80));
        OptionButton->setCheckable(true);
        OptionButton->setChecked(false);

        formLayout->setWidget(0, QFormLayout::FieldRole, OptionButton);


        retranslateUi(Option);

        QMetaObject::connectSlotsByName(Option);
    } // setupUi

    void retranslateUi(QWidget *Option)
    {
        Option->setWindowTitle(QApplication::translate("Option", "Form", Q_NULLPTR));
        OptionButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Option: public Ui_Option {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTION_H
