#ifndef CLEAR_COMMAND_H
#define CLEAR_COMMAND_H

#include <cell.h>

#include <QtWidgets/QUndoCommand>

#define BASE_ID 0
#define BASE_TYPE 0

class ClearCommand : public QUndoCommand {
 private:
  Cell* cell;
  size_t old_id;
  size_t old_type;

 public:
  ClearCommand(Cell* cell);

  void undo() override;
  void redo() override;

  ~ClearCommand();
};

ClearCommand::ClearCommand(Cell* cell)
    : cell(cell), old_id(cell->get_id()), old_type(cell->get_type()) {}

void ClearCommand::undo() { cell->set_data(old_id, old_type); }
void ClearCommand::redo() { cell->set_data(BASE_ID, BASE_TYPE); }

ClearCommand::~ClearCommand() {}

#endif  // CLEAR_COMMAND_H