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

MainWindow::MainWindow(QWidget* parent, Map* map) : QMainWindow(parent) {
  ItemsId* ids = new ItemsId();
  OptionSelected* current_option = new OptionSelected();

  this->ui.setupUi(this);
  this->setWindowTitle(WINDOW_TITLE);
  this->map_grid = new MapGrid(this, map, ids, current_option);
  this->file_manager = new FileManager(this->map_grid);
  this->ui.horizontalLayout_2->addWidget(this->map_grid);
  this->ui.horizontalLayout_2->addWidget(
      new OptionsContainer(this, 2, ids, current_option));
  this->setAcceptDrops(true);  // For drag and drop
}

void MainWindow::on_SpinBoxRows_valueChanged(int value) {
  // this->map->resize(value, this->columns);
}

void MainWindow::on_actionNew_File_triggered() {
  this->file_manager->new_file();
}

void MainWindow::on_actionOpen_File_triggered() { this->file_manager->open(); }

void MainWindow::on_actionSave_triggered() { this->file_manager->save(); }

void MainWindow::on_actionSave_As_triggered() { this->file_manager->save_as(); }

void MainWindow::closeEvent(QCloseEvent* event) {
  //! Ignore the event by default.. otherwise the window will be closed always.
  // event->ignore();
  this->file_manager->close();
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

    this->file_manager->open_file(file_path);
  }
}

MainWindow::~MainWindow() {}