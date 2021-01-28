#include "match_view.h"

#include <iostream>
#include <string>

#include "moc_match_view.cpp"

MatchView::MatchView(QWidget* parent, const Match& match, Match* match_selected)
    : QWidget(parent), match(match), match_selected(match_selected) {
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

void MatchView::handleMousePressEvent(QMouseEvent* event) {
  if (match_selected != nullptr) {
    std::cout << "hola" << std::endl;
    match_selected->copy(match);
  }
}

MatchView::~MatchView() {}