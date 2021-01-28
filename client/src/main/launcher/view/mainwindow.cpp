#include "../include/mainwindow.h"

#include <event_filter.h>

#include <QtWidgets/QMessageBox>

#include "../include/match_view.h"
#include "iostream"
#include "moc_mainwindow.cpp"
#define WINDOW_TITLE "Wolfenstein Launcher"

MainWindow::MainWindow(QWidget* parent, Server* server, Match* match_selected)
    : QMainWindow(parent), match_selected(match_selected) {
  ui.setupUi(this);
  setWindowTitle(WINDOW_TITLE);
  ui.scrollAreaWidgetContents->installEventFilter(new EventFilter());
  ui.RefreshButton->setEnabled(true);

  matches.push_back(Match());
  matches.push_back(Match(1, "mapa1", 0, 10, true));
  matches.push_back(Match(2, "mapa2", 0, 10, false));
}

void MainWindow::update() {
  _remove_matches();
  _add_matches();
}

void MainWindow::_remove_matches() {
  QVBoxLayout* vlayout = ui.matchesLayout;
  while (vlayout->count()) {
    QWidget* widget = vlayout->itemAt(0)->widget();
    if (widget) {
      vlayout->removeWidget(widget);
      delete widget;
    }
  }
}

void MainWindow::_add_matches() {
  if (matches.empty()) {
    QMessageBox msgBox;
    msgBox.setWindowTitle(WINDOW_TITLE);
    msgBox.setText("Not maches found");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
  }
  std::list<Match>::iterator it;
  for (it = matches.begin(); it != matches.end(); ++it) {
    MatchView* match_view = new MatchView(nullptr, *it, match_selected);
    ui.matchesLayout->addWidget(match_view);
  }
}

void MainWindow::on_RefreshButton_clicked() {
  match_selected->reset();
  update();
}

void MainWindow::on_JoinButton_clicked() {
  if (!match_selected->is_running()) {
    QApplication::quit();
  }
}

void MainWindow::on_NewButton_clicked() {}

void MainWindow::on_AddMatchButton_clicked() { _add_matches(); }

void MainWindow::closeEvent(QCloseEvent* event) { match_selected->reset(); }

MainWindow::~MainWindow() {}