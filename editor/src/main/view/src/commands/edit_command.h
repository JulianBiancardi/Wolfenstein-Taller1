#ifndef EDIT_COMMAND_H
#define EDIT_COMMAND_H

#include <cell.h>

#include <QtWidgets/QUndoCommand>

class EditCommand : public QUndoCommand {
 private:
  Cell* cell;
  size_t old_id;
  size_t new_id;

 public:
  EditCommand(Cell* cell, size_t new_id);

  void undo() override;
  void redo() override;

  ~EditCommand();
};

EditCommand::EditCommand(Cell* cell, size_t new_id)
    : cell(cell), old_id(cell->get_id()), new_id(new_id) {}

void EditCommand::undo() { cell->set_id(old_id); }
void EditCommand::redo() { cell->set_id(new_id); }

EditCommand::~EditCommand() {}

#endif  // EDIT_COMMAND_H
