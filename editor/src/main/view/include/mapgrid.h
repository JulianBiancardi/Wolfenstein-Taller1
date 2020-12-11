#ifndef MAPGRID_H
#define MAPGRID_H

#include <QtGui/QDragEnterEvent>
#include <QtGui/QDropEvent>
#include <QtWidgets/QWidget>
#include <string>

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

  // this event is called when the mouse enters the widgets area during a
  // drag/drop operation
  void dragEnterEvent(QDragEnterEvent* event);

  // this event is called when the drop operation is initiated at the widget
  void dropEvent(QDropEvent* event);

  void generate_yamlfile();
  void open_map(const std::string& file_path);

 private:
  Ui::MapGrid ui;
  Map* map;
  ItemsId* ids;
  OptionSelected* current_option;

  void generateCelds();
};

#endif  // MAPGRID_H
