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
  if (!this->map->saved()) {
    QMessageBox::critical(this, "Not saved file", "The file is not saved.");
    return;
  }

  // Create the FileDialog
  QString filters = "All files (*.*) ;; Yaml files (*.yaml)";
  QString file_path = QFileDialog::getOpenFileName(this, "Open File",
                                                   QDir::homePath(), filters);
  if (file_path.isEmpty()) {
    return;
  }
  try {
    this->current_file_path = file_path;
    std::cout << "opening file:" << this->current_file_path.toStdString()
              << std::endl;
    this->map->open_map(this->current_file_path.toStdString());
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    QMessageBox::critical(this, "Unknow file", "The file is not recognized.");
  }
}

void MainWindow::on_actionSave_triggered() {
  try {
    std::cout << "saving file in:" << std::endl;
    std::cout << this->current_file_path.toStdString() << std::endl;
    this->map->generate_yamlfile(this->current_file_path.toStdString());
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    QMessageBox::critical(this, "Error", "Cannot save the file.");
  }
}

void MainWindow::on_actionSave_As_triggered() {
  // Create the FileDialog
  QString filters = "All files (*.*) ;; Yaml files (*.yaml)";
  QString file_path = QFileDialog::getSaveFileName(this, "Savel File",
                                                   QDir::homePath(), filters);

  if (file_path.isEmpty()) {
    return;
  }
  // Add the extension
  if (!file_path.endsWith(".yaml")) {
    file_path += ".yaml";
  }

  try {
    this->current_file_path = file_path;
    this->map->generate_yamlfile(this->current_file_path.toStdString());
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    QMessageBox::critical(this, "Error", "Cannot save the file.");
  }
}
