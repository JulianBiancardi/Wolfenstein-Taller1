#include "match_view.h"

#include "moc_match_view.cpp"

MatchView::MatchView(QWidget* parent, const Match& match, Match* match_selected)
    : QWidget(parent),
      match_id(match.get_match_id()),
      match_selected(match_selected) {
  ui.setupUi(this);
  ui.name->setText(QString(match.get_map_name()));
  ui.current_players->setText(QString("%1").arg(match.get_players_joined()) +
                              " / " +
                              QString("%1").arg(match.get_players_total()));
  if (match.is_running()) {
    ui.status->setText(QString("in game"));
  } else {
    ui.status->setText(QString("wating"));
  }
}

void MatchView::handleSelectedEvent(QMouseEvent* event) {
  if (match_selected != nullptr) {
    printf("%u \n", match_id);
    match_selected->set_match_id(match_id);
  }
  this->setStyleSheet("background-color: rgb(136, 138, 133);");
}

void MatchView::handleDeselectedEvent(QMouseEvent* event) {
  this->setStyleSheet("background-color: rgb(211, 215, 207);");
}

MatchView::~MatchView() {}