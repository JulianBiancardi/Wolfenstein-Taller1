#ifndef DROP_COMMAND_H
#define DROP_COMMAND_H

#include <cell.h>

#include <QtWidgets/QUndoCommand>

#define BASE_ID 0
#define BASE_TYPE 0

class DropCommand : public QUndoCommand {
 private:
  Cell* cell_source;
  size_t old_type_source;
  size_t old_id_source;
  Cell* cell_dest;
  size_t old_type_dest;
  size_t old_id_dest;
  size_t new_type_dest;
  size_t new_id_dest;

 public:
  DropCommand(Cell* cell_source, Cell* cell_dest, size_t new_type_dest,
              size_t new_id_dest);

  void undo() override;
  void redo() override;

  ~DropCommand();
};

DropCommand::DropCommand(Cell* cell_source, Cell* cell_dest,
                         size_t new_type_dest, size_t new_id_dest)
    : cell_source(cell_source),
      old_type_source(cell_source->get_type()),
      old_id_source(cell_source->get_id()),
      cell_dest(cell_dest),
      old_type_dest(cell_dest->get_type()),
      old_id_dest(cell_dest->get_id()),
      new_type_dest(new_type_dest),
      new_id_dest(new_id_dest) {}

void DropCommand::undo() {
  cell_source->set_data(old_id_source, old_type_source);
  cell_dest->set_data(old_id_dest, old_type_dest);
}
void DropCommand::redo() {
  cell_source->set_data(BASE_ID, BASE_TYPE);
  cell_dest->set_data(new_id_dest, new_type_dest);
}

DropCommand::~DropCommand() {}

#endif  // DROP_COMMAND_H