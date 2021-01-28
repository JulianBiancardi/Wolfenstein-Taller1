#ifndef EVENT_FILTER_H
#define EVENT_FILTER_H

#include <match_view.h>

#include <QtCore/QDebug>
#include <QtCore/QEvent>
#include <QtCore/QObject>
#include <iostream>

class EventFilter : public QObject {
 private:
 public:
  EventFilter();

  bool eventFilter(QObject* watched, QEvent* event);

  ~EventFilter();
};

EventFilter::EventFilter() {}

bool EventFilter::eventFilter(QObject* watched, QEvent* event) {
  auto mouse_event = static_cast<QMouseEvent*>(event);

  if (event->type() == QEvent::MouseButtonPress) {
    auto widget = qApp->widgetAt(mouse_event->globalPos());
    if (MatchView* current_match = qobject_cast<MatchView*>(widget)) {
      qDebug() << widget;
      qDebug() << current_match;
      current_match->handleMousePressEvent(mouse_event);
      return true;
    }
    return false;
  } else {
    return false;
  }
}

EventFilter::~EventFilter() {}

#endif  // EVENT_FILTER_H