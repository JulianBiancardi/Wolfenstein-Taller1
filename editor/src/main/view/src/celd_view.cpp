#include "celd_view.h"

#include <QtCore/QMimeData>
#include <QtCore/QString>
#include <QtGui/QDrag>

#include "cell_mimedata.h"
#include "mapgrid.h"
#include "moc_celd_view.cpp"

CeldView::CeldView(QWidget* parent, Cell* celd, ItemsId* ids,
                   OptionSelected* current_option)
    : QWidget(parent), celd(celd), ids(ids), current_option(current_option) {
  this->ui.setupUi(this);
  this->celd->add_observer(this);
  this->setAcceptDrops(true);  // For drag and drop
  update();
}

CeldView::~CeldView() {}

// Controller
void CeldView::on_CeldButton_clicked() {
  this->celd->set_id(this->current_option->get_current_id());
}

void CeldView::mousePressEvent(QMouseEvent* event) {
  if (this->celd->is_empty()) {
    return;
  }
  if (event->button() == Qt::LeftButton) {
    this->celd->set_id(this->current_option->get_current_id());
  } else if (event->button() == Qt::RightButton) {
    this->celd->clear();
  }
}

void CeldView::mouseMoveEvent(QMouseEvent* event) {
  if (this->celd->is_empty()) {
    return;
  }
  if (!(event->buttons() & Qt::LeftButton)) {
    return;
  }
  // Preparate drag and drop system
  QPixmap pixmap(ids->get_icon_path(this->celd->get_id()));
  QDrag* drag = new QDrag(this);

  CellMimeData* mimeData = new CellMimeData(this->celd);
  drag->setMimeData(mimeData);
  drag->setPixmap(pixmap);
  drag->setHotSpot(QPoint(this->width() / 2, this->height() / 2));
  Qt::DropAction dropAction = drag->exec();
}

void CeldView::update() {
  QPixmap pixmap(ids->get_icon_path(this->celd->get_id()));
  QIcon CeldIcon(pixmap);
  this->ui.CeldButton->setIcon(CeldIcon);
  this->ui.CeldButton->setIconSize(pixmap.rect().size());
  // When change a celd the file is not more saved
  //((MapGrid*)this->parent()->parent()->parent())->set_saved(false);
}

void CeldView::dragEnterEvent(QDragEnterEvent* event) {
  // Not accept the drag if the celd is not empty
  if (!this->celd->is_empty()) {
    return;
  }
  event->acceptProposedAction();
}

void CeldView::dropEvent(QDropEvent* event) {
  Cell* cell_source = ((CellMimeData*)event->mimeData())->getcell_source();
  size_t id_source = cell_source->get_id();
  cell_source->clear();
  this->celd->set_id(id_source);
}
