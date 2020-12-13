#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QDragEnterEvent>
#include <QtGui/QDropEvent>
#include <QtWidgets/QMainWindow>

#include "mapgrid.h"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 private:
  Ui::MainWindow ui;
  MapGrid* map;
  QString current_file_path;
  bool is_saved;

  void save_file(QString& file_path);
  void open_file(QString& file_path);
  void no_saved_message();

 public:
  MainWindow(QWidget* parent = nullptr);

  // this event is called when the mouse enters the widgets area during a
  // drag/drop operation
  void dragEnterEvent(QDragEnterEvent* event);

  // this event is called when the drop operation is initiated at the widget
  void dropEvent(QDropEvent* event);

  ~MainWindow();

 private slots:
  void on_SpinBoxRows_valueChanged(int value);
  void on_actionNew_File_triggered();
  void on_actionOpen_File_triggered();
  void on_actionSave_triggered();
  void on_actionSave_As_triggered();

  // Close aplication signal
  void closeEvent(QCloseEvent* event) override;
};
#endif  // MAINWINDOW_H
