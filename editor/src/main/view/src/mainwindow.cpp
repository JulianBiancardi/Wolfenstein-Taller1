#include "mainwindow.h"

#include <QtCore/QDebug>  //TODO Delete
#include <QtCore/QDir>
#include <QtCore/QMimeData>  //Data for drag and drop system
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>

#include "../model/include/map_generator.h"
#include "iostream"
#include "itemsid.h"
#include "moc_mainwindow.cpp"
#include "option_selected.h"
#include "options_container.h"

#define WINDOW_TITLE "Wolfenstein Editor"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  ItemsId* ids = new ItemsId();
  OptionSelected* current_option = new OptionSelected();

  ui.setupUi(this);
  setWindowTitle(WINDOW_TITLE);
  map_grid = new MapGrid(this, ids, current_option);
  file_manager = new FileManager(map_grid);
  ui.horizontalLayout_2->addWidget(map_grid);
  ui.horizontalLayout_2->addWidget(
      new OptionsContainer(this, 2, ids, current_option));
  setAcceptDrops(true);  // For drag and drop
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

void MainWindow::dragEnterEvent(QDragEnterEvent* event) {
  std::cout << "Drag enter event" << std::endl;
  event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent* event) {
  qDebug() << "dropEvent" << event;
  const QMimeData* mimeData = event->mimeData();

  if (mimeData->hasUrls()) {
    QList<QUrl> urlList = mimeData->urls();
    // extract only the first file
    QString file_path = urlList.first().toLocalFile();
    file_manager->open_file(file_path);
  }
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

MainWindow::~MainWindow() {}