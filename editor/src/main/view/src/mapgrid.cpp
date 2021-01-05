#include "mapgrid.h"

#include "../../model/include/map_generator.h"
#include "celd_view.h"
#include "iostream"
#include "moc_mapgrid.cpp"

#define INVALID_ID -1

//-----------------------------------------------------------------------------
MapGrid::MapGrid(QWidget* parent, ItemsId* ids, OptionSelected* current_option)
    : QWidget(parent), ids(ids), current_option(current_option) {
  this->ui.setupUi(this);
  map = new Map();
  this->ui.scrollContent->setLayout(new QGridLayout());
  generateCelds();
}

void MapGrid::generateCelds() {
  QGridLayout* gridlayout = (QGridLayout*)ui.scrollContent->layout();
  for (size_t row = 0; row < map->row_count(); row++) {
    for (size_t column = 0; column < map->column_count(); column++) {
      CeldView* celd_view = new CeldView(this, map->at(row, column), this->ids,
                                         this->current_option);
      gridlayout->addWidget(celd_view, row, column);
    }
  }
}

void MapGrid::clear() { map->clear_all(); }

void MapGrid::insert_rowabove() {
  map->insert_rowabove();
  resize();
}
void MapGrid::insert_rowbelow() {
  map->insert_rowbelow();
  resize();
}
void MapGrid::insert_columnright() {
  map->insert_columnright();
  resize();
}
void MapGrid::insert_columnleft() {
  map->insert_columnleft();
  resize();
}
void MapGrid::remove_rowabove() {
  map->remove_rowabove();
  resize();
}
void MapGrid::remove_rowbelow() {
  map->remove_rowbelow();
  resize();
}
void MapGrid::remove_columnleft() {
  map->remove_columnleft();
  resize();
}
void MapGrid::remove_columnright() {
  map->remove_columnright();
  resize();
}

void MapGrid::_remove_cells() {
  QGridLayout* gridlayout = (QGridLayout*)ui.scrollContent->layout();
  for (size_t row = 0; row < map->row_count(); row++) {
    for (size_t column = 0; column < map->column_count(); column++) {
      delete gridlayout->itemAtPosition(row, column);
    }
  }
}

void MapGrid::resize() {
  QGridLayout* gridlayout = (QGridLayout*)this->ui.scrollContent->layout();
  for (size_t row = 0; row < map->row_count(); row++) {
    for (size_t column = 0; column < map->column_count(); column++) {
      CeldView* celd_view = new CeldView(this, map->at(row, column), this->ids,
                                         this->current_option);
      gridlayout->addWidget(celd_view, row, column);
    }
  }
}

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

MapGrid::~MapGrid() { _remove_cells(); }
