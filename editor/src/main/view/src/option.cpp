#include "option.h"

#include <stdexcept>  //Runtime error

// Incluyo el archivo creado por el moc para que cmake lo detecte y compile
#include "moc_option.cpp"

//-----------------------------------------------------------------------------
Option::Option(QWidget* parent, size_t id, const QString& name,
               const QString& icon_path, OptionSelected* current_option)
    : QWidget(parent),
      id(id),
      name(name),
      icon(icon_path),
      current_option(current_option) {
  if (current_option == nullptr) {
    throw std::runtime_error("Error to create Option");
  } else {
    ui.setupUi(this);
    QIcon ButtonIcon(icon);
    ui.OptionButton->setIcon(ButtonIcon);
  }
}

Option::~Option() {}

QPushButton* Option::getButton() { return ui.OptionButton; }

void Option::on_OptionButton_clicked() {
  current_option->set_info(id, name, icon);
}
//-----------------------------------------------------------------------------
