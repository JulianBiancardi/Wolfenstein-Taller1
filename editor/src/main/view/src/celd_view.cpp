#include "celd_view.h"

#include "iostream"
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

void CeldView::update() {
  std::cout << "Updating celd" << std::endl;

  QPixmap pixmap(ids->get_icon_path(this->celd->get_id()));
  QIcon CeldIcon(pixmap);
  this->ui.CeldButton->setIcon(CeldIcon);
  this->ui.CeldButton->setIconSize(pixmap.rect().size());
}
