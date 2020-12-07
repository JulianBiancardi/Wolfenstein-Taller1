/********************************************************************************
** Form generated from reading UI file 'mapgrid.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPGRID_H
#define UI_MAPGRID_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MapGrid
{
public:
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollContent;

    void setupUi(QWidget *MapGrid)
    {
        if (MapGrid->objectName().isEmpty())
            MapGrid->setObjectName(QStringLiteral("MapGrid"));
        MapGrid->resize(529, 412);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MapGrid->sizePolicy().hasHeightForWidth());
        MapGrid->setSizePolicy(sizePolicy);
        MapGrid->setMinimumSize(QSize(0, 0));
        gridLayout = new QGridLayout(MapGrid);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(MapGrid);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        sizePolicy.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy);
        scrollArea->setStyleSheet(QStringLiteral("background-color: rgb(85, 255, 127);"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setWidgetResizable(true);
        scrollContent = new QWidget();
        scrollContent->setObjectName(QStringLiteral("scrollContent"));
        scrollContent->setGeometry(QRect(0, 0, 529, 412));
        scrollArea->setWidget(scrollContent);

        gridLayout->addWidget(scrollArea, 0, 0, 1, 1);


        retranslateUi(MapGrid);

        QMetaObject::connectSlotsByName(MapGrid);
    } // setupUi

    void retranslateUi(QWidget *MapGrid)
    {
        MapGrid->setWindowTitle(QApplication::translate("MapGrid", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MapGrid: public Ui_MapGrid {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPGRID_H
