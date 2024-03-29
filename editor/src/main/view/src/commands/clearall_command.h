#ifndef CLEARALL_COMMAND_H
#define CLEARALL_COMMAND_H

#include <cell.h>
#include <map.h>

#include <QtWidgets/QUndoCommand>
#include <map>

class ClearAllCommand : public QUndoCommand {
 private:
  Map* map;
  std::map<Cell*, std::pair<size_t, size_t>> old_types_ids;

 public:
  ClearAllCommand(Map* map);

  void undo() override;
  void redo() override;

  ~ClearAllCommand();
};

ClearAllCommand::ClearAllCommand(Map* map) : map(map) {
  for (size_t row = 0; row < map->row_count(); row++) {
    for (size_t column = 0; column < map->column_count(); column++) {
      Cell* cell = map->at(row, column);
      if (!cell->is_empty()) {
        old_types_ids.insert(std::make_pair(
            cell, std::make_pair(cell->get_type(), cell->get_id())));
      }
    }
  }
}

void ClearAllCommand::undo() {
  std::map<Cell*, std::pair<size_t, size_t>>::iterator it;
  for (it = old_types_ids.begin(); it != old_types_ids.end(); it++) {
    it->first->set_data(it->second.second, it->second.first);
  }
}
void ClearAllCommand::redo() { map->clear_all(); }

ClearAllCommand::~ClearAllCommand() {}

#endif  // CLEARALL_COMMAND_H