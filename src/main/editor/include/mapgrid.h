#ifndef MAPGRID_H
#define MAPGRID_H

#include <QWidget>

#include "itemsid.h"
#include "option_selected.h"
#include "ui_mapgrid.h"

class MapGrid : public QWidget {
  Q_OBJECT

 public:
  MapGrid(QWidget* parent = nullptr, int rows = 50, int columns = 50,
          ItemsId* ids = nullptr, OptionSelected* current_option = nullptr);
  ~MapGrid();

  void clear();

 private:
  Ui::MapGrid ui;
  int rows;
  int columns;
  OptionSelected* current_option;

  void generateCelds(ItemsId* ids, OptionSelected* current_option);
};

#endif  // MAPGRID_H
