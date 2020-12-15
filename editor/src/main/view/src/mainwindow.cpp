#include "mainwindow.h"

#include <QtCore/QDebug>  //TODO Delete
#include <QtCore/QDir>
#include <QtCore/QMimeData>  //Data for drag and drop system
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>

#include "../model/include/map.h"
#include "../model/include/map_generator.h"
#include "iostream"
#include "itemsid.h"
#include "moc_mainwindow.cpp"
#include "option_selected.h"
#include "options_container.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), current_file_path(""), is_saved(false) {
  ItemsId* ids = new ItemsId();
  OptionSelected* current_option = new OptionSelected();

  // Generate the initial map
  Map* map = new Map(10, 10);

  this->ui.setupUi(this);
  this->map = new MapGrid(this, map, ids, current_option);
  this->ui.horizontalLayout_2->addWidget(this->map);
  this->ui.horizontalLayout_2->addWidget(
      new OptionsContainer(this, 2, ids, current_option));
  this->setAcceptDrops(true);  // For drag and drop
}

void MainWindow::save_file(QString& file_path) {
  try {
    std::cout << "saving file in:" << std::endl;
    std::cout << file_path.toStdString() << std::endl;
    this->map->generate_yamlfile(file_path.toStdString());
    this->is_saved = true;
    this->current_file_path = file_path;
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    QMessageBox::critical(this, "Error", "Cannot save the file.");
  }
}

void MainWindow::open_file(QString& file_path) {
  try {
    std::cout << "opening file:" << file_path.toStdString() << std::endl;
    this->map->open_map(file_path.toStdString());
    this->is_saved = true;
    this->current_file_path = file_path;
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    QMessageBox::critical(this, "Unknow file", "The file is not recognized.");
  }
}

void MainWindow::no_saved_message() {
  //! EntitiesSaverObserver::Instance()->isAllSaved()
  if (!this->is_saved) {
    QString strToShow = QString("Some files has been created or modified...");
    QMessageBox msgBox;
    msgBox.setParent(this);
    msgBox.setText(strToShow);
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setDefaultButton(QMessageBox::Save);

    switch (msgBox.exec()) {
      case QMessageBox::Save: {
        // Save was clicked
        qDebug() << "Save changes";
        on_actionSave_triggered();
        break;
      }
      case QMessageBox::Discard: {
        // Don't Save was clicked
        qDebug() << "Discard changes and open the file";
        // open the file
        QString filters = "All files (*.*) ;; Yaml files (*.yaml)";
        QString file_path = QFileDialog::getOpenFileName(
            this, "Open File", QDir::homePath(), filters);

        open_file(file_path);

        break;
      }
      default:
        // should never be reached
        break;
    }
  } else {
    // Do not need to save nothing...
    QString filters = "All files (*.*) ;; Yaml files (*.yaml)";
    QString file_path = QFileDialog::getOpenFileName(this, "Open File",
                                                     QDir::homePath(), filters);

    open_file(file_path);
  }
}

void MainWindow::on_SpinBoxRows_valueChanged(int value) {
  // this->map->resize(value, this->columns);
}

void MainWindow::on_actionNew_File_triggered() {
  std::cout << "new file" << std::endl;
  this->map->clear();
  this->current_file_path = "";
  this->is_saved = false;
}

void MainWindow::on_actionOpen_File_triggered() {
  //! EntitiesSaverObserver::Instance()->isAllSaved()
  if (!this->is_saved) {
    QString strToShow = QString("Some files has been created or modified...");
    QMessageBox msgBox;
    msgBox.setParent(this);
    msgBox.setText(strToShow);
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setDefaultButton(QMessageBox::Save);

    switch (msgBox.exec()) {
      case QMessageBox::Save: {
        // Save was clicked
        qDebug() << "Save changes";
        on_actionSave_triggered();
        break;
      }
      case QMessageBox::Cancel: {
        // Don't Save was clicked
        qDebug() << "Discard changes and open the file";
        // open the file
        QString filters = "All files (*.*) ;; Yaml files (*.yaml)";
        QString file_path = QFileDialog::getOpenFileName(
            this, "Open File", QDir::homePath(), filters);

        open_file(file_path);
        break;
      }
      default:
        // should never be reached
        break;
    }
  } else {
    // Do not need to save nothing...
    QString filters = "All files (*.*) ;; Yaml files (*.yaml)";
    QString file_path = QFileDialog::getOpenFileName(this, "Open File",
                                                     QDir::homePath(), filters);
    open_file(file_path);
  }
}

void MainWindow::on_actionSave_triggered() {
  if (this->current_file_path.isEmpty()) {
    on_actionSave_As_triggered();
  } else {
    save_file(this->current_file_path);
  }
}

void MainWindow::on_actionSave_As_triggered() {
  // Create the FileDialog
  QString filters = "All files (*.*) ;; Yaml files (*.yaml)";
  QString file_path = QFileDialog::getSaveFileName(this, "Savel File",
                                                   QDir::homePath(), filters);

  // Necesary
  if (file_path.isEmpty()) {
    return;
  }
  // Add the extension
  if (!file_path.endsWith(".yaml")) {
    file_path += ".yaml";
  }
  save_file(file_path);
}

void MainWindow::closeEvent(QCloseEvent* event) {
  //! Ignore the event by default.. otherwise the window will be closed always.
  event->ignore();

  //! EntitiesSaverObserver::Instance()->isAllSaved()
  if (!this->is_saved) {
    QString strToShow = QString("Some files has been created or modified...");
    QMessageBox msgBox;
    msgBox.setParent(this);
    msgBox.setText(strToShow);
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard |
                              QMessageBox::Cancel);
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setDefaultButton(QMessageBox::Save);

    switch (msgBox.exec()) {
      case QMessageBox::Save: {
        // Save was clicked
        qDebug() << "Save changes and quit";
        if (this->current_file_path.isEmpty()) {
          on_actionSave_As_triggered();
        } else {
          on_actionSave_triggered();
        }
        event->accept();
        break;
      }
      case QMessageBox::Discard: {
        // Don't Save was clicked
        qDebug() << "Discard changes";
        event->accept();
        break;
      }
      case QMessageBox::Cancel: {
        // Cancel was clicked
        qDebug() << "No quit the aplication";
        break;
      }
      default:
        // should never be reached
        break;
    }
  } else {
    event->accept();  // Do not need to save nothing... accept the event and
                      // close the app
  }
}

void MainWindow::dragEnterEvent(QDragEnterEvent* event) {
  std::cout << "Drag enter event" << std::endl;
  event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent* event) {
  // TODO FIX THE CRASH WHEN THE DROP FILE IS NOT A YAML FILE !!!!!!!!!

  qDebug() << "dropEvent" << event;

  const QMimeData* mimeData = event->mimeData();

  // check for our needed mime type, here a file or a list of files
  if (mimeData->hasUrls()) {
    // QStringList pathList;
    QList<QUrl> urlList = mimeData->urls();

    /*
        // extract the local paths of the files
        for (int i = 0; i < urlList.size() && i < 32; + i) {
          pathList.append(urlList.at(i).toLocalFile());
        }*/

    // extract only the first file
    QString file_path = urlList.first().toLocalFile();

    // call a function to open the files
    // openFiles(pathList);
    open_file(file_path);
  }
}

MainWindow::~MainWindow() {}