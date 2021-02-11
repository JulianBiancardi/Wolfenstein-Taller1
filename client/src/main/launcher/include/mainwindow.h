#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QCloseEvent>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

#include "../../server.h"
#include "launcher.h"
#include "match.h"
#include "settings.h"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 private:
  Ui::MainWindow ui;
  Server* server;
  std::string map_selected;
  Match* match_selected;
  Launcher launcher;

  void _remove_matches();
  void _add_matches();
  void _add_maps();

 public:
  MainWindow(QWidget* parent = nullptr, Server* server = nullptr,
             Settings* settings = nullptr, Match* match_selected = nullptr);
  ~MainWindow();

  /*Update the match list*/
  void update();
  /*Set the current page to show*/
  void set_page(size_t page_id);

 private slots:
  void on_SettingsButton_clicked();
  void on_RefreshButton_clicked();
  void on_JoinButton_clicked();
  void on_NewButton_clicked();
  void on_CreateButton_clicked();
  void on_CancelButton_clicked();
  void closeEvent(QCloseEvent* event) override;
};
#endif  // MAINWINDOW_H
