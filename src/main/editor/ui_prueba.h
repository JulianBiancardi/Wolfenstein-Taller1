/********************************************************************************
** Form generated from reading UI file 'prueba.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRUEBA_H
#define UI_PRUEBA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Prueba
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *Prueba)
    {
        if (Prueba->objectName().isEmpty())
            Prueba->setObjectName(QStringLiteral("Prueba"));
        Prueba->resize(400, 300);
        verticalLayout = new QVBoxLayout(Prueba);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton = new QPushButton(Prueba);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(Prueba);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);


        retranslateUi(Prueba);

        QMetaObject::connectSlotsByName(Prueba);
    } // setupUi

    void retranslateUi(QWidget *Prueba)
    {
        Prueba->setWindowTitle(QApplication::translate("Prueba", "Form", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Prueba", "PushButton", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("Prueba", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Prueba: public Ui_Prueba {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRUEBA_H
