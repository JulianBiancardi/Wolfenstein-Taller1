#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QDragEnterEvent>
#include <QtGui/QDropEvent>
#include <QtWidgets/QMainWindow>

#include "file_manager.h"
#include "mapgrid.h"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 private:
  Ui::MainWindow ui;
  MapGrid* map_grid;
  FileManager* file_manager;

 public:
  MainWindow(QWidget* parent = nullptr);

  // this event is called when the mouse enters the widgets area during a
  // drag/drop operation
  void dragEnterEvent(QDragEnterEvent* event);

  // this event is called when the drop operation is initiated at the widget
  void dropEvent(QDropEvent* event);

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
