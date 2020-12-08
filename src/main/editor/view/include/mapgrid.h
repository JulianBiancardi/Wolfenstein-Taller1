#ifndef MAPGRID_H
#define MAPGRID_H

#include <QtWidgets/QWidget>

#include "../model/include/map.h"
#include "itemsid.h"
#include "option_selected.h"
#include "ui_mapgrid.h"

class MapGrid : public QWidget {
  Q_OBJECT

 public:
  MapGrid(QWidget* parent = nullptr, Map* map = nullptr, ItemsId* ids = nullptr,
          OptionSelected* current_option = nullptr);
  ~MapGrid();

  void clear();
  // Resize the map size
  void resize(size_t new_rows, size_t new_columns);

  void generate_yamlfile();

 private:
  Ui::MapGrid ui;
  Map* map;
  ItemsId* ids;
  OptionSelected* current_option;

  void generateCelds();
};

#endif  // MAPGRID_H
