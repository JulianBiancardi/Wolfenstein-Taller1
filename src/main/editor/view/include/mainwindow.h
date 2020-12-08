#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "mapgrid.h"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private slots:
  void on_GenerateFileButton_clicked();
  void on_SpinBoxRows_valueChanged(int value);

 private:
  Ui::MainWindow ui;
  MapGrid* map;
  size_t rows = 10;
  size_t columns = 10;
};
#endif  // MAINWINDOW_H
