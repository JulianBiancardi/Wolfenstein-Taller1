#include "../include/mainwindow.h"

#include <event_filter.h>

#include <QtWidgets/QMessageBox>

#include "../include/match_view.h"
#include "iostream"
#include "moc_mainwindow.cpp"
#define WINDOW_TITLE "Wolfenstein Launcher"

static void _show_error(const QString& message) {
  QMessageBox msgBox;
  msgBox.setWindowTitle(WINDOW_TITLE);
  msgBox.setText(message);
  msgBox.setStandardButtons(QMessageBox::Ok);
  msgBox.exec();
}

MainWindow::MainWindow(QWidget* parent, Server* server, Match* match_selected)
    : QMainWindow(parent), match_selected(match_selected), launcher(server) {
  ui.setupUi(this);
  setWindowTitle(WINDOW_TITLE);
  ui.scrollAreaWidgetContents->installEventFilter(new EventFilter());
  ui.RefreshButton->setEnabled(true);

  _update();
}

void MainWindow::_update() {
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
  std::list<Match> matches = launcher.get_matches();
  if (matches.empty()) {
    _show_error("Not maches found");
  }
  std::list<Match>::iterator it;
  for (it = matches.begin(); it != matches.end(); ++it) {
    MatchView* match_view = new MatchView(nullptr, *it, match_selected);
    ui.matchesLayout->addWidget(match_view);
  }
}

void MainWindow::on_RefreshButton_clicked() {
  match_selected->reset();
  launcher.update_matches();
  _update();
}

void MainWindow::on_JoinButton_clicked() {
  if (launcher.join_match(match_selected->get_match_id()) !=
      match_selected->get_match_id()) {
    _show_error("Failed to join the match");
  } else {
    // Succed to join the match, close the application and continue
    // with the game
    QApplication::quit();
  }
}

void MainWindow::on_NewButton_clicked() {
  // TODO CREATE OTHER WINDOW or other secction
  match_selected->set_match_id(launcher.create_match("new_map"));
  if (match_selected->get_match_id() == INVALID_ID) {
    _show_error("Failed to create the match");
  } else {
    // Succed to create the new match, close the application and continue
    // with the game
    QApplication::quit();
  }
}

void MainWindow::closeEvent(QCloseEvent* event) { match_selected->reset(); }

MainWindow::~MainWindow() {}