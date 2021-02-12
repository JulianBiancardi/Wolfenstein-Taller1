#include "map_view.h"

#include "moc_map_view.cpp"

MapView::MapView(QWidget* parent, const MapOption& map,
                 std::string& map_selected)
    : QWidget(parent), map_selected(map_selected) {
  ui.setupUi(this);
  ui.Name->setText(QString(map.get_map_name().c_str()));
  ui.Capacity->setText(
      QString(std::to_string(map.get_players_total()).c_str()));
}

void MapView::handleSelectedEvent(QMouseEvent* event) {
  map_selected = ui.Name->text().toStdString();
  this->setStyleSheet("background-color: rgb(136, 138, 133);");
}

void MapView::handleDeselectedEvent(QMouseEvent* event) {
  this->setStyleSheet("background-color: rgb(211, 215, 207);");
}

MapView::~MapView() {}