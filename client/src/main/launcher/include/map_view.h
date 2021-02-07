#ifndef MAP_VIEW_H
#define MAP_VIEW_H

#include <QtWidgets/QWidget>

#include "ui_map_view.h"

class MapView : public QWidget {
  Q_OBJECT

 private:
  Ui::MapView ui;

 public:
  MapView(QWidget* parent = nullptr);

  void handleSelectedEvent(QMouseEvent* event);
  void handleDeselectedEvent(QMouseEvent* event);

  ~MapView();
};
#endif  // MAP_VIEW_H