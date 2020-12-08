#include "mainwindow.h"

#include "../model/include/map.h"
#include "../model/include/map_generator.h"
#include "QtCore/QDir"
#include "QtWidgets/QFileDialog"
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

void MainWindow::on_GenerateFileButton_clicked() {
  this->map->generate_yamlfile();
}

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
  }
}
