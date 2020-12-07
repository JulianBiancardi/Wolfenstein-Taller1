/********************************************************************************
** Form generated from reading UI file 'options_container.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONS_CONTAINER_H
#define UI_OPTIONS_CONTAINER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OptionContainer
{
public:
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;

    void setupUi(QWidget *OptionContainer)
    {
        if (OptionContainer->objectName().isEmpty())
            OptionContainer->setObjectName(QStringLiteral("OptionContainer"));
        OptionContainer->resize(302, 565);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(OptionContainer->sizePolicy().hasHeightForWidth());
        OptionContainer->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(OptionContainer);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(OptionContainer);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy1);
        QFont font;
        font.setKerning(true);
        scrollArea->setFont(font);
        scrollArea->setStyleSheet(QStringLiteral("background-color: rgb(64, 68, 75);"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setLineWidth(1);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 302, 565));
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 0, 0, 1, 1);


        retranslateUi(OptionContainer);

        QMetaObject::connectSlotsByName(OptionContainer);
    } // setupUi

    void retranslateUi(QWidget *OptionContainer)
    {
        OptionContainer->setWindowTitle(QApplication::translate("OptionContainer", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class OptionContainer: public Ui_OptionContainer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONS_CONTAINER_H
