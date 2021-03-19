#ifndef MAPGRID_H
#define MAPGRID_H

#include <QtWidgets/QUndoStack>
#include <QtWidgets/QWidget>
#include <string>

#include "../../model/include/Iobserver.h"
#include "../../model/include/map.h"
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
  QUndoStack* undostack;

  void _remove_cells();
  void generateCelds();

 public:
  MapGrid(QWidget* parent = nullptr, ItemsId* ids = nullptr,
          OptionSelected* current_option = nullptr);

  void update() override;
  void clear();
  void undo();
  void redo();

  size_t rowscount() const;
  size_t columnscount() const;

  // Resize the map size
  void insert_rowabove(size_t count);
  void insert_rowbelow(size_t count);
  void insert_columnright(size_t count);
  void insert_columnleft(size_t count);
  void remove_rowabove(size_t count);
  void remove_rowbelow(size_t count);
  void remove_columnright(size_t count);
  void remove_columnleft(size_t count);

  void open_map(const std::string& file_path);
  void generate_yamlfile(const std::string& file_path);

  // TODO DELETE
  void init(ItemsId* ids, OptionSelected* current_option);

  ~MapGrid();
};

#endif  // MAPGRID_H
