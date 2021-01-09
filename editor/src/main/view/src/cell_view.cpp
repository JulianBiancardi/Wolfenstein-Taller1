#include "cell_view.h"

#include <QtCore/QMimeData>
#include <QtCore/QString>
#include <QtGui/QDrag>

#include "cell_mimedata.h"
#include "iostream"
#include "mapgrid.h"
#include "moc_cell_view.cpp"

CellView::CellView(QWidget* parent, Cell* cell, ItemsId* ids,
                   OptionSelected* current_option)
    : QWidget(parent), cell(cell), ids(ids), current_option(current_option) {
  if (cell == nullptr) {
    return;  // TODO ERROR
  }
  ui.setupUi(this);
  cell->add_observer(this);
  setAcceptDrops(true);
  update();
}

void CellView::on_CellButton_clicked() {
  cell->set_id(current_option->get_current_id());
}

void CellView::mousePressEvent(QMouseEvent* event) {
  if (cell->is_empty()) {
    return;
  }
  if (event->button() == Qt::LeftButton) {
    cell->set_id(current_option->get_current_id());
  } else if (event->button() == Qt::RightButton) {
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
  ui.CellButton->setIconSize(pixmap.rect().size());
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
  size_t id_source = cell_source->get_id();
  cell_source->clear();
  cell->set_id(id_source);
}

CellView::~CellView() {
  if (cell != nullptr) {
    cell->remove_observer(this);
  }
}
