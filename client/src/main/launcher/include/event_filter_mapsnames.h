#ifndef EVENT_FILTER_MAPSNAMES_H
#define EVENT_FILTER_MAPSNAMES_H

#include <map_view.h>

#include <QtCore/QDebug>
#include <QtCore/QEvent>
#include <QtCore/QObject>
#include <QtGui/QMouseEvent>

class EventFilterMapsNames : public QObject {
 private:
  MapView* last_map = nullptr;
  MapView* current_map = nullptr;

 public:
  EventFilterMapsNames();

  bool eventFilter(QObject* watched, QEvent* event);

  ~EventFilterMapsNames();
};

EventFilterMapsNames::EventFilterMapsNames() {}

bool EventFilterMapsNames::eventFilter(QObject* watched, QEvent* event) {
  auto mouse_event = static_cast<QMouseEvent*>(event);

  if (event->type() == QEvent::MouseButtonPress) {
    auto widget = qApp->widgetAt(mouse_event->globalPos());
    current_map = qobject_cast<MapView*>(widget);
    if (current_map == nullptr) {
      current_map = qobject_cast<MapView*>(widget->parent());
      if (current_map == nullptr) {
        return false;
      }
    }

    current_map->handleSelectedEvent(mouse_event);
    if (last_map != nullptr) {
      last_map->handleDeselectedEvent(mouse_event);
    }
    last_map = current_map;
    return true;

  } else {
    return false;
  }
}

EventFilterMapsNames::~EventFilterMapsNames() {}

#endif  // EVENT_FILTER_MAPSNAMES_H