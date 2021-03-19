#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QCloseEvent>
#include <QtWidgets/QMainWindow>

#include "file_manager.h"
#include "itemsid.h"
#include "option_selected.h"
#include "ui_editorwindow.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 private:
  Ui::EditorWindow ui;
  ItemsId* ids;
  OptionSelected* current_option;
  FileManager* file_manager;

 public:
  MainWindow(QWidget* parent = nullptr);

  ~MainWindow();

 private slots:
  void on_actionNew_File_triggered();
  void on_actionOpen_File_triggered();
  void on_actionSave_triggered();
  void on_actionSave_As_triggered();
  void on_actionExit_triggered();

  void on_actionUndo_triggered();
  void on_actionRedo_triggered();

  // Close aplication signal
  void closeEvent(QCloseEvent* event) override;
};
#endif  // MAINWINDOW_H
