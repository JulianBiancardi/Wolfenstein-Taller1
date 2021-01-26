#include "mainwindow.h"

#include "iostream"
#include "moc_mainwindow.cpp"

#define WINDOW_TITLE "Wolfenstein Launcher"

MainWindow::MainWindow(QWidget* parent, Server* server, Match* match_selected)
    : QMainWindow(parent), match_selected(match_selected), launcher(server) {
  ui.setupUi(this);
  setWindowTitle(WINDOW_TITLE);
  launcher.add_observer(this);
}

void MainWindow::update() {
  _remove_matches();
  std::list<Match> matches = launcher.get_matches();
  std::list<Match>::iterator it;
  for (it = matches.begin(); it != matches.end(); ++it) {
    MatchView* match_view = new MatchView(it->get_match_id());
  }
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

void MainWindow::on_RefreshButton_clicked() { launcher.update_matches(); }

void MainWindow::on_JoinButton_clicked();

void MainWindow::on_NewButton_clicked();

void MainWindow::closeEvent(QCloseEvent* event) {}

MainWindow::~MainWindow() {}