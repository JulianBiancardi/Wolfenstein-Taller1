#include "file_manager.h"

#include <QtCore/QDebug>  //TODO Delete
#include <QtCore/QDir>
#include <QtGui/QCloseEvent>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>

#define WINDOW_TITLE "Wolfenstein Editor"

//----------------------------------------------
FileManager::FileManager(MapGrid* map_grid)
    : map_grid(map_grid), current_file_path(""), is_saved(false) {}

void FileManager::no_saved_message() {
  QMessageBox msgBox;
  msgBox.setWindowTitle(WINDOW_TITLE);
  msgBox.setText("Some files has been created or modified...");
  msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
  msgBox.setInformativeText("Do you want to save your changes?");
  msgBox.setDefaultButton(QMessageBox::Save);

  switch (msgBox.exec()) {
    case QMessageBox::Save: {
      qDebug() << "Save changes";
      save();
      break;
    }
    case QMessageBox::Cancel:
    default:
      // should never be reached
      break;
  }
}

void FileManager::save_file(const QString& file_path) {
  try {
    this->map_grid->generate_yamlfile(file_path.toStdString());
    this->is_saved = true;
    this->current_file_path = file_path;
  } catch (const std::exception& e) {
    QMessageBox::critical(nullptr, "Error", "Cant save the file.");
  }
}

void FileManager::open_file(const QString& file_path) {
  try {
    this->map_grid->open_map(file_path.toStdString());
    this->is_saved = true;
    this->current_file_path = file_path;
  } catch (const std::exception& e) {
    QMessageBox::critical(nullptr, "Unknow file",
                          "The file is not recognized.");
  }
}

void FileManager::new_file() {
  if (!this->is_saved) {
    no_saved_message();
  }
  this->map_grid->clear();
  this->current_file_path = "";
  this->is_saved = false;
}

void FileManager::save() {
  if (this->current_file_path.isEmpty()) {
    save_as();
  } else {
    save_file(this->current_file_path);
  }
}

void FileManager::save_as() {
  // Create the FileDialog
  QString filters = "All files (*.*) ;; Yaml files (*.yaml)";
  QString file_path = QFileDialog::getSaveFileName(nullptr, "Save File",
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

void FileManager::open() {
  if (!this->is_saved) {
    no_saved_message();
  }
  // Do not need to save nothing...
  QString filters = "All files (*.*) ;; Yaml files (*.yaml)";
  QString file_path = QFileDialog::getOpenFileName(nullptr, "Open File",
                                                   QDir::homePath(), filters);
  open_file(file_path);
}

void FileManager::close() {
  if (!this->is_saved) {
    no_saved_message();
  }
}

FileManager::~FileManager() {}