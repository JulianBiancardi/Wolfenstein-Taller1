#include "celd.h"

#include "iostream"
#include "moc_celd.cpp"

Celd::Celd(QWidget* parent, ItemsId* ids, OptionSelected* current_option)
    : QWidget(parent), ids(ids), current_option(current_option) {
  this->ui.setupUi(this);
}

Celd::~Celd() {}

void Celd::on_CeldButton_clicked() {
  // Update celd
  QPixmap pixmap(ids->getImagePath(current_option->getCurrent_id()));
  QIcon CeldIcon(pixmap);
  this->ui.CeldButton->setIcon(CeldIcon);
  this->ui.CeldButton->setIconSize(pixmap.rect().size());
}

void Celd::on_CeldButton_pressed() { std::cout << "Cel pressed" << std::endl; }
