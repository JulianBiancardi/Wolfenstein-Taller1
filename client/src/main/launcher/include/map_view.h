#ifndef MAP_VIEW_H
#define MAP_VIEW_H

#include <QtWidgets/QWidget>

#include "map_option.h"
#include "ui_map_view.h"

static MapOption map_default;

static std::string default_map_selected;

class MapView : public QWidget {
  Q_OBJECT

 private:
  Ui::MapView ui;
  std::string& map_selected;

 public:
  MapView(QWidget* parent = nullptr, const MapOption& map = map_default,
          std::string& map_selected = default_map_selected);

  void handleSelectedEvent(QMouseEvent* event);
  void handleDeselectedEvent(QMouseEvent* event);

  ~MapView();
};
#endif  // MAP_VIEW_H