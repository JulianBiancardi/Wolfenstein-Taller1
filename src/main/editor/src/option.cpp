#include "option.h"

#include <stdexcept>  //Runtime error

#include "iostream"
// Incluyo el archivo creado por el moc para que cmake lo detecte y compile
#include "moc_option.cpp"

//-----------------------------------------------------------------------------
Option::Option(QWidget* parent, size_t id, ItemsId* ids,
               OptionSelected* current_option)
    : QWidget(parent), id(id), current_option(current_option) {
  if (ids == nullptr || current_option == nullptr) {
    // TODO exception
    throw std::runtime_error("Error to create Option");
  } else {
    this->ui.setupUi(this);
    QPixmap pixmap(ids->getImagePath(id));
    QIcon ButtonIcon(pixmap);
    this->ui.OptionButton->setIcon(ButtonIcon);
  }
}

Option::~Option() {}

QPushButton* Option::getButton() { return this->ui.OptionButton; }

void Option::on_OptionButton_clicked() {
  current_option->setCurrent_id(this->id);
}
//-----------------------------------------------------------------------------
