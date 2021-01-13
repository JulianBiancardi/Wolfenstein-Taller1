#ifndef DROP_COMMAND_H
#define DROP_COMMAND_H

#include <cell.h>

#include <QtWidgets/QUndoCommand>

#define BASE_ID 0

class DropCommand : public QUndoCommand {
 private:
  Cell* cell_source;
  size_t old_id_source;
  Cell* cell_dest;
  size_t old_id_dest;
  size_t new_id_dest;

 public:
  DropCommand(Cell* cell_source, Cell* cell_dest, size_t new_id_dest);

  void undo() override;
  void redo() override;

  ~DropCommand();
};

DropCommand::DropCommand(Cell* cell_source, Cell* cell_dest, size_t new_id_dest)
    : cell_source(cell_source),
      old_id_source(cell_source->get_id()),
      cell_dest(cell_dest),
      old_id_dest(cell_dest->get_id()),
      new_id_dest(new_id_dest) {}

void DropCommand::undo() {
  cell_source->set_id(old_id_source);
  cell_dest->set_id(old_id_dest);
}
void DropCommand::redo() {
  cell_source->set_id(BASE_ID);
  cell_dest->set_id(new_id_dest);
}

DropCommand::~DropCommand() {}

#endif  // DROP_COMMAND_H