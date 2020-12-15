#ifndef MAPGRID_H
#define MAPGRID_H

#include <QtWidgets/QWidget>
#include <string>

#include "../model/include/map.h"
#include "itemsid.h"
#include "option_selected.h"
#include "ui_mapgrid.h"

class MapGrid : public QWidget {
  Q_OBJECT

 private:
  Ui::MapGrid ui;
  Map* map;
  ItemsId* ids;
  OptionSelected* current_option;

 public:
  MapGrid(QWidget* parent = nullptr, Map* map = nullptr, ItemsId* ids = nullptr,
          OptionSelected* current_option = nullptr);
  ~MapGrid();

  void clear();
  // Resize the map size
  void resize(size_t new_rows, size_t new_columns);

  void open_map(const std::string& file_path);
  void generate_yamlfile(const std::string& file_path);

  void generateCelds();
};

#endif  // MAPGRID_H
