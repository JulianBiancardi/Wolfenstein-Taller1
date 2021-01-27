#ifndef MATCH_VIEW_H
#define MATCH_VIEW_H

#include <QtWidgets/QWidget>

#include "match.h"
#include "ui_match_view.h"

static Match match_default;

class MatchView : public QWidget {
  Q_OBJECT

 private:
  Ui::MatchView ui;
  const Match& match;
  Match* match_selected;

 public:
  MatchView(QWidget* parent = nullptr, const Match& match = match_default,
            Match* match_selected = nullptr);

  void mousePressEvent(QMouseEvent* event);

  ~MatchView();
};
#endif  // MATCH_VIEW_H