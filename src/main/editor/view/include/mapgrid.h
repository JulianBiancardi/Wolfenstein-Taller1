#ifndef MAPGRID_H
#define MAPGRID_H

#include <QtWidgets/QWidget>

#include "../model/include/map.h"
#include "itemsid.h"
#include "option_selected.h"
#include "ui_mapgrid.h"

static Map df_map;
static ItemsId df_ids_mapgrid;
static OptionSelected df_current_option_mapgrid;

class MapGrid : public QWidget {
  Q_OBJECT

 public:
  MapGrid(QWidget* parent = nullptr, Map& map = df_map,
          ItemsId& ids = df_ids_mapgrid,
          OptionSelected& current_option = df_current_option_mapgrid);
  ~MapGrid();

  void clear();
  // Resize the map size
  void resize(size_t new_rows, size_t new_columns);

  void generate_yamlfile();

 private:
  Ui::MapGrid ui;
  Map& map;
  ItemsId& ids;
  OptionSelected& current_option;

  void generateCelds();
};

#endif  // MAPGRID_H
