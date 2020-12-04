#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMediaPlayer>
#include <QUrl>
#include <option.h>
#include "mapgrid.h"
#include "options_container.h"
#include "itemsid.h"
#include "optionselected.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ItemsId* ids = new ItemsId();
    OptionSelected* current_option = new OptionSelected();

    ui->setupUi(this);
    ui->horizontalLayout_2->addWidget(new MapGrid(this,5,5,ids,current_option));
    ui->horizontalLayout_2->addWidget(new OptionsContainer(this,2,2,ids,current_option));
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_ClearButton_clicked(){

}
