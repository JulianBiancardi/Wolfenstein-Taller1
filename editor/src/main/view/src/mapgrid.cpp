#include "mapgrid.h"

#include <clearall_command.h>

#include <QtWidgets/QGraphicsDropShadowEffect>

#include "../../model/include/map_generator.h"
#include "cell_view.h"
#include "iostream"
#include "moc_mapgrid.cpp"

//-----------------------------------------------------------------------------
MapGrid::MapGrid(QWidget* parent, ItemsId* ids, OptionSelected* current_option)
    : QWidget(parent), ids(ids), current_option(current_option) {
  ui.setupUi(this);
  QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
  shadowEffect->setColor(QColor(0, 0, 0, 255 * 0.3));
  shadowEffect->setXOffset(-4);
  shadowEffect->setYOffset(4);
  shadowEffect->setBlurRadius(12);
  setGraphicsEffect(shadowEffect);

  undostack = new QUndoStack(this);
  map = new Map();
  map->add_observer(this);
  // generateCelds();
}

void MapGrid::init(ItemsId* ids,
                   OptionSelected* current_option) {  // TODO DELETE
  this->ids = ids;
  this->current_option = current_option;
  generateCelds();
}

void MapGrid::update() {
  // Clear the undo stack
  undostack->clear();
  generateCelds();
}

void MapGrid::generateCelds() {
  QGridLayout* gridlayout = ui.CellGrid;
  for (size_t row = 0; row < map->row_count(); row++) {
    for (size_t column = 0; column < map->column_count(); column++) {
      CellView* cell_view = new CellView(this, map->at(row, column), ids,
                                         current_option, undostack);
      gridlayout->addWidget(cell_view, row, column);
    }
  }
}

void MapGrid::_remove_cells() {
  QGridLayout* gridlayout = ui.CellGrid;
  while (gridlayout->count()) {
    QWidget* widget = gridlayout->itemAt(0)->widget();
    if (widget) {
      gridlayout->removeWidget(widget);
      delete widget;
    }
  }
}

size_t MapGrid::rowscount() const { return map->row_count(); }
size_t MapGrid::columnscount() const { return map->column_count(); }

void MapGrid::undo() { undostack->undo(); }
void MapGrid::redo() { undostack->redo(); }

void MapGrid::clear() {
  ClearAllCommand* cmd = new ClearAllCommand(map);
  undostack->push(cmd);
  map->clear_all();
}
void MapGrid::insert_rowabove(size_t count) {
  _remove_cells();
  map->insert_rowabove(count);
}
void MapGrid::insert_rowbelow(size_t count) {
  _remove_cells();
  map->insert_rowbelow(count);
}
void MapGrid::insert_columnright(size_t count) {
  _remove_cells();
  map->insert_columnright(count);
}
void MapGrid::insert_columnleft(size_t count) {
  _remove_cells();
  map->insert_columnleft(count);
}
void MapGrid::remove_rowabove(size_t count) {
  _remove_cells();
  map->remove_rowabove(count);
}
void MapGrid::remove_rowbelow(size_t count) {
  _remove_cells();
  map->remove_rowbelow(count);
}
void MapGrid::remove_columnleft(size_t count) {
  _remove_cells();
  map->remove_columnleft(count);
}
void MapGrid::remove_columnright(size_t count) {
  _remove_cells();
  map->remove_columnright(count);
}

void MapGrid::open_map(const std::string& file_path) {
  if (file_path.empty()) {
    return;
  }
  _remove_cells();
  undostack->clear();
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
