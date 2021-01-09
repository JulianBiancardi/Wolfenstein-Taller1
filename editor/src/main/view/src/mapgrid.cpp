#include "mapgrid.h"

#include "../../model/include/map_generator.h"
#include "cell_view.h"
#include "iostream"
#include "moc_mapgrid.cpp"

//-----------------------------------------------------------------------------
MapGrid::MapGrid(QWidget* parent, ItemsId* ids, OptionSelected* current_option)
    : QWidget(parent), ids(ids), current_option(current_option) {
  ui.setupUi(this);
  map = new Map();
  map->add_observer(this);
  QGridLayout* gridlayout = new QGridLayout();
  gridlayout->setSpacing(0);
  ui.scrollContent->setLayout(gridlayout);
  generateCelds();
}

void MapGrid::update() { generateCelds(); }

void MapGrid::generateCelds() {
  QGridLayout* gridlayout = (QGridLayout*)ui.scrollContent->layout();
  for (size_t row = 0; row < map->row_count(); row++) {
    for (size_t column = 0; column < map->column_count(); column++) {
      CellView* cell_view =
          new CellView(this, map->at(row, column), ids, current_option);
      gridlayout->addWidget(cell_view, row, column);
    }
  }
}

void MapGrid::_remove_cells() {
  QGridLayout* gridlayout = (QGridLayout*)ui.scrollContent->layout();
  while (gridlayout->count()) {
    QWidget* widget = gridlayout->itemAt(0)->widget();
    if (widget) {
      gridlayout->removeWidget(widget);
      delete widget;
    }
  }
  // delete gridlayout;
  // TODO see to replace the gridlayout
}

void MapGrid::clear() { map->clear_all(); }
void MapGrid::insert_rowabove() {
  _remove_cells();
  map->insert_rowabove();
}
void MapGrid::insert_rowbelow() {
  _remove_cells();
  map->insert_rowbelow();
}
void MapGrid::insert_columnright() {
  _remove_cells();
  map->insert_columnright();
}
void MapGrid::insert_columnleft() {
  _remove_cells();
  map->insert_columnleft();
}
void MapGrid::remove_rowabove() {
  _remove_cells();
  map->remove_rowabove();
}
void MapGrid::remove_rowbelow() {
  _remove_cells();
  map->remove_rowbelow();
}
void MapGrid::remove_columnleft() {
  _remove_cells();
  map->remove_columnleft();
}
void MapGrid::remove_columnright() {
  _remove_cells();
  map->remove_columnright();
}

void MapGrid::open_map(const std::string& file_path) {
  if (file_path.empty()) {
    return;
  }
  _remove_cells();
  delete map;
  MapGenerator map_generator;
  map = map_generator.generate_map(file_path);
  map->add_observer(this);

  generateCelds();
}

void MapGrid::generate_yamlfile(const std::string& file_path) {
  MapGenerator file_generator;
  file_generator.generate_yamlfile(file_path, map);
}

MapGrid::~MapGrid() {
  // delete map;
}
