#ifndef EVENT_FILTER_H
#define EVENT_FILTER_H

#include <match_view.h>

#include <QtCore/QDebug>
#include <QtCore/QEvent>
#include <QtCore/QObject>
#include <QtGui/QMouseEvent>

class EventFilter : public QObject {
 private:
  MatchView* last_match = nullptr;
  MatchView* current_match = nullptr;

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
    current_match = qobject_cast<MatchView*>(widget);
    if (current_match == nullptr) {
      current_match = qobject_cast<MatchView*>(widget->parent());
      if (current_match == nullptr) {
        return false;
      }
    }

    current_match->handleSelectedEvent(mouse_event);
    if (last_match != nullptr) {
      last_match->handleDeselectedEvent(mouse_event);
    }
    last_match = current_match;
    return true;

  } else {
    return false;
  }
}

EventFilter::~EventFilter() {}

#endif  // EVENT_FILTER_H