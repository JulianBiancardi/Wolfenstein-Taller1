#include "mapgrid.h"

#include "../../model/include/map_generator.h"
#include "cell_view.h"
#include "iostream"
#include "moc_mapgrid.cpp"

#define INVALID_ID -1

//-----------------------------------------------------------------------------
MapGrid::MapGrid(QWidget* parent, ItemsId* ids, OptionSelected* current_option)
    : QWidget(parent), ids(ids), current_option(current_option) {
  ui.setupUi(this);
  map = new Map();
  map->add_observer(this);
  ui.scrollContent->setLayout(new QGridLayout());
  generateCelds();
}

void MapGrid::update() {
  _remove_cells();
  generateCelds();
}

void MapGrid::generateCelds() {
  QGridLayout* gridlayout = (QGridLayout*)ui.scrollContent->layout();
  if (gridlayout == nullptr) return;
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
  // TODO see to replace the gridlayout
}

void MapGrid::clear() { map->clear_all(); }

void MapGrid::insert_rowabove() { map->insert_rowabove(); }
void MapGrid::insert_rowbelow() { map->insert_rowbelow(); }
void MapGrid::insert_columnright() { map->insert_columnright(); }
void MapGrid::insert_columnleft() { map->insert_columnleft(); }
void MapGrid::remove_rowabove() { map->remove_rowabove(); }
void MapGrid::remove_rowbelow() { map->remove_rowbelow(); }
void MapGrid::remove_columnleft() { map->remove_columnleft(); }
void MapGrid::remove_columnright() { map->remove_columnright(); }

void MapGrid::open_map(const std::string& file_path) {
  if (file_path.empty()) {
    return;
  }

  MapGenerator map_generator;
  map = map_generator.generate_map(file_path);
  map->print();
  generateCelds();
}

void MapGrid::generate_yamlfile(const std::string& file_path) {
  MapGenerator file_generator;
  file_generator.generate_yamlfile(file_path, map);
}

MapGrid::~MapGrid() {
  _remove_cells();
  delete map;
}
