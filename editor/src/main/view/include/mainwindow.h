#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QCloseEvent>
#include <QtWidgets/QMainWindow>

#include "file_manager.h"
#include "itemsid.h"
#include "mapgrid.h"
#include "option_selected.h"
#include "options_container.h"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 private:
  Ui::MainWindow ui;
  ItemsId* ids;
  OptionSelected* current_option;
  MapGrid* map_grid;
  OptionsContainer* options_container;
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

  void on_actionInsertRowsAbove_triggered();
  void on_actionInsertRowsBelow_triggered();
  void on_actionInsertColumnsLeft_triggered();
  void on_actionInsertColumnsRight_triggered();
  void on_actionRemoveRowsAbove_triggered();
  void on_actionRemoveRowsBelow_triggered();
  void on_actionRemoveColumnsLeft_triggered();
  void on_actionRemoveColumnsRight_triggered();

  // Close aplication signal
  void closeEvent(QCloseEvent* event) override;
};
#endif  // MAINWINDOW_H
