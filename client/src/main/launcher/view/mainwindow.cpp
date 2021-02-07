#include "../include/mainwindow.h"

#include <QtWidgets/QMessageBox>

#include "../include/event_filter.h"
#include "../include/map_view.h"
#include "../include/match_view.h"
#include "moc_mainwindow.cpp"

#define WINDOW_TITLE "Wolfenstein Launcher"
#define MATCHLIST_PAGE 0
#define NEWMATCH_PAGE 1

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
  ui.stackedWidget->setCurrentIndex(MATCHLIST_PAGE);
  _add_maps();
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

void MainWindow::_add_maps() {
  // TODO
  std::list<Match> maps = launcher.get_maps();

  std::list<Match>::iterator it;
  for (it = maps.begin(); it != maps.end(); ++it) {
    MapView* map_view = new MapView(nullptr);
    ui.mapsLayout->addWidget(map_view);
  }
}

void MainWindow::on_RefreshButton_clicked() {
  ui.scrollAreaWidgetContents->installEventFilter(new EventFilter());
  match_selected->reset();
  launcher.update_matches();
  update();
}

void MainWindow::on_JoinButton_clicked() {
  if (!match_selected->is_valid()) {
    _show_error("No match selected");
    return;
  }
  if (launcher.join_match(match_selected->get_match_id()) ==
      match_selected->get_match_id()) {
    // Succed to join the match, close the application and continue
    // with the game
    QApplication::quit();
  } else {
    _show_error("Failed to join the match");
  }
}

void MainWindow::on_NewButton_clicked() {
  ui.stackedWidget->setCurrentIndex(NEWMATCH_PAGE);
}

void MainWindow::on_CreateButton_clicked() {
  match_selected->set_match_id(launcher.create_match("test_map"));
  if (match_selected->is_valid()) {
    // Succed to create the new match, close the application and continue
    // with the game
    QApplication::quit();
  } else {
    _show_error("Failed to create the match");
  }
}

void MainWindow::on_CancelButton_clicked() {
  ui.stackedWidget->setCurrentIndex(MATCHLIST_PAGE);
}

void MainWindow::closeEvent(QCloseEvent* event) { match_selected->reset(); }

MainWindow::~MainWindow() {}