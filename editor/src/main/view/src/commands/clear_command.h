#ifndef CLEAR_COMMAND_H
#define CLEAR_COMMAND_H

#include <cell.h>

#include <QtWidgets/QUndoCommand>

#define BASE_ID 0

class ClearCommand : public QUndoCommand {
 private:
  Cell* cell;
  size_t old_id;

 public:
  ClearCommand(Cell* cell);

  void undo() override;
  void redo() override;

  ~ClearCommand();
};

ClearCommand::ClearCommand(Cell* cell) : cell(cell), old_id(cell->get_id()) {}

void ClearCommand::undo() { cell->set_id(old_id); }
void ClearCommand::redo() { cell->set_id(BASE_ID); }

ClearCommand::~ClearCommand() {}

#endif  // CLEAR_COMMAND_H