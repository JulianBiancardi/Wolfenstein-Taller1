#include "mainwindow.h"

#include "itemsid.h"
#include "mapgrid.h"
#include "moc_mainwindow.cpp"
#include "option_selected.h"
#include "options_container.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  ItemsId* ids = new ItemsId();
  OptionSelected* current_option = new OptionSelected();

  this->ui.setupUi(this);
  this->ui.horizontalLayout_2->addWidget(
      new MapGrid(this, 5, 5, ids, current_option));
  this->ui.horizontalLayout_2->addWidget(
      new OptionsContainer(this, 2, ids, current_option));
}

MainWindow::~MainWindow() {}

void MainWindow::on_ClearButton_clicked() {}
