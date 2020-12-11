#include "mainwindow.h"

#include <QtCore/QDir>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>

#include "../model/include/map.h"
#include "../model/include/map_generator.h"
#include "iostream"
#include "itemsid.h"
#include "moc_mainwindow.cpp"
#include "option_selected.h"
#include "options_container.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  ItemsId* ids = new ItemsId();
  OptionSelected* current_option = new OptionSelected();

  // Generate the initial map
  Map* map = new Map(10, 10);

  this->ui.setupUi(this);
  this->map = new MapGrid(this, map, ids, current_option);
  this->ui.horizontalLayout_2->addWidget(this->map);
  this->ui.horizontalLayout_2->addWidget(
      new OptionsContainer(this, 2, ids, current_option));
}

MainWindow::~MainWindow() {}

void MainWindow::on_SpinBoxRows_valueChanged(int value) {
  // this->map->resize(value, this->columns);
}

void MainWindow::on_actionNew_File_triggered() {
  std::cout << "new file" << std::endl;
}

void MainWindow::on_actionOpen_File_triggered() {
  std::cout << "open file" << std::endl;
  // Create the FileDialog
  QString filters = "All files (*.*) ;; Yaml files (*.yaml)";
  QString file_path = QFileDialog::getOpenFileName(this, "Open File",
                                                   QDir::homePath(), filters);
  try {
    this->map->open_map(file_path.toStdString());
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    QMessageBox::critical(this, "Unknow file", "The file is not recognized.");
  }
}

void MainWindow::on_actionSave_triggered() {
  std::cout << "saving file" << std::endl;
}

void MainWindow::on_actionSave_As_triggered() {
  std::cout << "saving file as..." << std::endl;
  // Create the FileDialog
  QString filters = "All files (*.*) ;; Yaml files (*.yaml)";
  QString file_path = QFileDialog::getSaveFileName(this, "Savel File",
                                                   QDir::homePath(), filters);

  this->map->generate_yamlfile(file_path.toStdString());
  /*
try {
this->map->open_map(file_path.toStdString());
} catch (const std::exception& e) {
std::cerr << e.what() << '\n';
QMessageBox::critical(this, "Unknow file", "The file is not recognized.");
}*/
}
