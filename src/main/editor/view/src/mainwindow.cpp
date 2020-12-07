#include "mainwindow.h"

#include "itemsid.h"
#include "moc_mainwindow.cpp"
#include "option_selected.h"
#include "options_container.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  ItemsId* ids = new ItemsId();
  OptionSelected* current_option = new OptionSelected();

  this->ui.setupUi(this);
  this->map = new MapGrid(this, this->rows, this->columns, ids, current_option);
  this->ui.horizontalLayout_2->addWidget(map);
  this->ui.horizontalLayout_2->addWidget(
      new OptionsContainer(this, 2, ids, current_option));
}

MainWindow::~MainWindow() {}

void MainWindow::on_GenerateFileButton_clicked() {
  this->map->generate_yamlfile();
}

void MainWindow::on_SpinBoxRows_valueChanged(int value) {
  this->map->resize(value, this->columns);
}
