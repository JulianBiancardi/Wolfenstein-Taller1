#include "cell_view.h"

#include <clear_command.h>
#include <drop_command.h>
#include <edit_command.h>

#include <QtCore/QMimeData>
#include <QtCore/QString>
#include <QtGui/QDrag>

#include "cell_mimedata.h"
#include "iostream"
#include "mapgrid.h"
#include "moc_cell_view.cpp"

CellView::CellView(QWidget* parent, Cell* cell, ItemsId* ids,
                   OptionSelected* current_option, QUndoStack* undostack)
    : QWidget(parent),
      cell(cell),
      ids(ids),
      current_option(current_option),
      undostack(undostack) {
  if (cell == nullptr) {
    return;  // TODO ERROR
  }
  ui.setupUi(this);
  cell->add_observer(this);
  setAcceptDrops(true);
  update();
}

void CellView::on_CellButton_clicked() {
  size_t id = current_option->get_current_id();
  EditCommand* cmd = new EditCommand(cell, id);
  undostack->push(cmd);
  cell->set_id(id);
}

void CellView::mousePressEvent(QMouseEvent* event) {
  if (cell->is_empty()) {
    return;
  }
  if (event->button() == Qt::LeftButton) {
    cell->set_id(current_option->get_current_id());
  } else if (event->button() == Qt::RightButton) {
    ClearCommand* cmd = new ClearCommand(cell);
    undostack->push(cmd);
    cell->clear();
  }
}

void CellView::mouseMoveEvent(QMouseEvent* event) {
  if (cell->is_empty()) {
    return;
  }
  if (!(event->buttons() & Qt::LeftButton)) {
    return;
  }
  // Preparate drag and drop system
  QPixmap pixmap(ids->get_icon_path(cell->get_id()));
  pixmap =
      pixmap.scaled(QSize(ui.CellButton->width(), ui.CellButton->height()));

  QDrag* drag = new QDrag(this);
  CellMimeData* mimeData = new CellMimeData(cell);
  drag->setMimeData(mimeData);
  drag->setPixmap(pixmap);
  drag->setHotSpot(QPoint(this->width() / 2, this->height() / 2));
  Qt::DropAction dropAction = drag->exec();
}

void CellView::update() {
  QPixmap pixmap(ids->get_icon_path(cell->get_id()));
  QIcon CellIcon(pixmap);
  ui.CellButton->setIcon(CellIcon);
  ui.CellButton->setIconSize(
      QSize(ui.CellButton->width(), ui.CellButton->height()));
}

void CellView::dragEnterEvent(QDragEnterEvent* event) {
  // Not accept the drag if the cell is not empty
  if (!cell->is_empty()) {
    return;
  }
  event->acceptProposedAction();
}

void CellView::dropEvent(QDropEvent* event) {
  Cell* cell_source = ((CellMimeData*)event->mimeData())->getcell_source();
  DropCommand* cmd = new DropCommand(cell_source, cell, cell_source->get_id());
  cell->set_id(cell_source->get_id());
  undostack->push(cmd);
  cell_source->clear();
}

CellView::~CellView() {
  if (cell != nullptr) {
    cell->remove_observer(this);
  }
}
