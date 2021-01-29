#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Iobserver.h>

#include <QtGui/QCloseEvent>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

#include "../../server.h"
#include "launcher.h"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow, public IObserver {
  Q_OBJECT

 private:
  Ui::MainWindow ui;
  Server* server;
  Match* match_selected;
  Launcher launcher;

  void _remove_matches();
  void _add_matches();

 public:
  MainWindow(QWidget* parent = nullptr, Server* server = nullptr,
             Match* match_selected = nullptr);

  ~MainWindow();

  void update() override;

 private slots:
  void on_RefreshButton_clicked();
  void on_JoinButton_clicked();
  void on_NewButton_clicked();
  void closeEvent(QCloseEvent* event) override;
};
#endif  // MAINWINDOW_H
