#include "mainwindow.h"

#include "../model/include/map_generator.h"
#include "iostream"
#include "moc_mainwindow.cpp"

#define WINDOW_TITLE "Wolfenstein Editor"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  ui.setupUi(this);
  setWindowTitle(WINDOW_TITLE);
  ids = new ItemsId();
  current_option = new OptionSelected();
  map_grid = new MapGrid(this, ids, current_option);
  options_container = new OptionsContainer(this, 2, ids, current_option);
  file_manager = new FileManager(map_grid);
  ui.horizontalLayout_2->addWidget(map_grid);
  ui.horizontalLayout_2->addWidget(options_container);
}

void MainWindow::on_actionNew_File_triggered() { file_manager->new_file(); }

void MainWindow::on_actionOpen_File_triggered() { file_manager->open(); }

void MainWindow::on_actionSave_triggered() { file_manager->save(); }

void MainWindow::on_actionSave_As_triggered() { file_manager->save_as(); }

void MainWindow::on_actionExit_triggered() {
  file_manager->close();
  QApplication::quit();
}

void MainWindow::closeEvent(QCloseEvent* event) {
  file_manager->close();
  event->accept();
}

void MainWindow::on_actionInsertRowsAbove_triggered() {
  map_grid->insert_rowabove();
}
void MainWindow::on_actionInsertRowsBelow_triggered() {
  map_grid->insert_rowbelow();
}
void MainWindow::on_actionInsertColumnsLeft_triggered() {
  map_grid->insert_columnleft();
}
void MainWindow::on_actionInsertColumnsRight_triggered() {
  map_grid->insert_columnright();
}
void MainWindow::on_actionRemoveRowsAbove_triggered() {
  map_grid->remove_rowabove();
}
void MainWindow::on_actionRemoveRowsBelow_triggered() {
  map_grid->remove_rowbelow();
}
void MainWindow::on_actionRemoveColumnsLeft_triggered() {
  map_grid->remove_columnleft();
}
void MainWindow::on_actionRemoveColumnsRight_triggered() {
  map_grid->remove_columnright();
}

MainWindow::~MainWindow() {
  delete ids;
  delete current_option;
  delete map_grid;
  delete options_container;
  delete file_manager;
}