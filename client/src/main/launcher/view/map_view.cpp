#include "map_view.h"

#include "moc_map_view.cpp"

MapView::MapView(QWidget* parent) : QWidget(parent) {
  ui.setupUi(this);
  ui.Name->setText("test");
  ui.Capacity->setText("5");
}

void MapView::handleSelectedEvent(QMouseEvent* event) {
  this->setStyleSheet("background-color: rgb(136, 138, 133);");
}

void MapView::handleDeselectedEvent(QMouseEvent* event) {
  this->setStyleSheet("background-color: rgb(211, 215, 207);");
}

MapView::~MapView() {}