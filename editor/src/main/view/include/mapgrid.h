#ifndef MAPGRID_H
#define MAPGRID_H

#include <QtWidgets/QWidget>
#include <string>

#include "../model/include/Iobserver.h"
#include "../model/include/map.h"
#include "itemsid.h"
#include "option_selected.h"
#include "ui_mapgrid.h"

class MapGrid : public QWidget, public IObserver {
  Q_OBJECT

 private:
  Ui::MapGrid ui;
  Map* map;
  ItemsId* ids;
  OptionSelected* current_option;

  void _remove_cells();
  void resize();

 public:
  MapGrid(QWidget* parent = nullptr, ItemsId* ids = nullptr,
          OptionSelected* current_option = nullptr);
  ~MapGrid();

  void generateCelds();
  void clear();

  void update() override;

  // Resize the map size
  void insert_rowabove();
  void insert_rowbelow();
  void insert_columnright();
  void insert_columnleft();
  void remove_rowabove();
  void remove_rowbelow();
  void remove_columnright();
  void remove_columnleft();

  void open_map(const std::string& file_path);
  void generate_yamlfile(const std::string& file_path);
};

#endif  // MAPGRID_H
