#ifndef EVENT_FILTER_H
#define EVENT_FILTER_H

#include <cell_view.h>
#include <option_selected.h>

#include <QtCore/QDebug>
#include <QtCore/QObject>
#include <iostream>
#define PAINT_STATE 1
#define DRAG_STATE 2

class EventFilter : public QObject {
 private:
  CellView* lastCell;
  OptionSelected* current_option;

 public:
  EventFilter(OptionSelected* current_option);

  bool eventFilter(QObject* watched, QEvent* event);

  ~EventFilter();
};

EventFilter::EventFilter(OptionSelected* current_option)
    : current_option(current_option) {}

bool EventFilter::eventFilter(QObject* watched, QEvent* event) {
  auto mouse_event = static_cast<QMouseEvent*>(event);
  auto current_cell = qobject_cast<CellView*>(watched);

  switch (current_option->state()) {
    case PAINT_STATE:
      if (event->type() == QEvent::MouseMove) {
        auto widget = qApp->widgetAt(mouse_event->globalPos())->parent();
        auto currentCell = qobject_cast<CellView*>(widget);
        if (currentCell == nullptr) {
          return false;
        }
        if ((mouse_event->buttons() & Qt::LeftButton) == Qt::LeftButton) {
          currentCell->handleMouseMoveEventInsidePaint(mouse_event);
          return true;

        } else if ((mouse_event->buttons() & Qt::RightButton) ==
                   Qt::RightButton) {
          currentCell->handleMouseMoveEventInsideClear(mouse_event);
          return true;
        }
      }
      if (event->type() == QEvent::MouseButtonPress) {
        current_cell->handleMousePressEvent(mouse_event);
        return true;
      }
      return false;
      break;
    case DRAG_STATE:
      if (event->type() == QEvent::MouseMove) {
        if ((mouse_event->buttons() & Qt::LeftButton) == Qt::LeftButton) {
          current_cell->handleMouseMoveEventInsideDrag(mouse_event);
          return true;
        }
      }
      return false;
      break;
    default:
      return false;
      break;
  }
}

EventFilter::~EventFilter() {}

#endif  // EVENT_FILTER_H