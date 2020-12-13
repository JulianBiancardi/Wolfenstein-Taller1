#include "celd_view.h"

#include <QtCore/QMimeData>  //Data for drag and drop system
#include <QtCore/QString>
#include <QtGui/QDrag>  //Drag system

#include "iostream"  //TODO delete
#include "mapgrid.h"
#include "moc_celd_view.cpp"

CeldView::CeldView(QWidget* parent, Celd* celd, ItemsId* ids,
                   OptionSelected* current_option)
    : QWidget(parent), celd(celd), ids(ids), current_option(current_option) {
  this->ui.setupUi(this);
  this->celd->add_observer(this);
}

CeldView::~CeldView() {}

// Controller
void CeldView::on_CeldButton_clicked() {
  // Update celd info
  this->celd->set_id(this->current_option->get_current_id());
}

// Controller
void CeldView::on_CeldButton_pressed() {
  /*
  if (this->celd->get_id() == 0) {
    return;
  }
  // Preparate drag and drop system
  std::cout << "Star drag and drop" << std::endl;
  QPixmap pixmap(ids->get_icon_path(this->celd->get_id()));
  QDrag* drag = new QDrag(this);
  QMimeData* mimeData = new QMimeData;

  drag->setMimeData(mimeData);
  drag->setPixmap(pixmap);

  mimeData->setText("1");
  Qt::DropAction dropAction = drag->exec();
  // Qt::DropAction dropAction = drag->exec();
  // drag->setHotSpot(event->pos() - this->pos());*/
}

void CeldView::mousePressEvent(QMouseEvent* event) {
  /*
  if (this->celd->get_id() == 0) {
    return;
  }
  /*
    if (event->button() == Qt::LeftButton) {
    }

  std::cout << "Star drag and drop" << std::endl;
  QPixmap pixmap(ids->get_icon_path(this->celd->get_id()));
  QDrag* drag = new QDrag(this);
  QMimeData* mimeData = new QMimeData;

  drag->setMimeData(mimeData);
  drag->setPixmap(pixmap);

  mimeData->setText("1");
  Qt::DropAction dropAction = drag->exec();*/
}

void CeldView::update() {
  QPixmap pixmap(ids->get_icon_path(this->celd->get_id()));
  QIcon CeldIcon(pixmap);
  this->ui.CeldButton->setIcon(CeldIcon);
  this->ui.CeldButton->setIconSize(pixmap.rect().size());
  // When change a celd the file is not more saved
  ((MapGrid*)this->parent()->parent()->parent())->set_saved(false);
}

void CeldView::dragEnterEvent(QDragEnterEvent* event) {
  if (event->mimeData()->hasText()) {
    event->acceptProposedAction();
  }
  event->acceptProposedAction();
}

void CeldView::dropEvent(QDragEnterEvent* event) {
  std::cout << "Drop event" << std::endl;

  this->celd->set_id(event->mimeData()->text().toInt());

  // event->acceptProposedAction();
}
