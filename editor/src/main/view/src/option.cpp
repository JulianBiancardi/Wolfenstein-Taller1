#include "option.h"

#include <stdexcept>  //Runtime error

#include "iostream"
// Incluyo el archivo creado por el moc para que cmake lo detecte y compile
#include "moc_option.cpp"

//-----------------------------------------------------------------------------
Option::Option(QWidget* parent, size_t id, const QString& tooltip,
               const QString& icon_path, OptionSelected* current_option)
    : QWidget(parent), id(id), current_option(current_option) {
  if (current_option == nullptr) {
    // TODO exception
    throw std::runtime_error("Error to create Option");
  } else {
    std::cout << tooltip.toStdString() << " " << icon_path.toStdString()
              << std::endl;
    this->ui.setupUi(this);
    QPixmap pixmap(icon_path);
    QIcon ButtonIcon(pixmap);
    this->ui.OptionButton->setIcon(ButtonIcon);
    this->ui.OptionButton->setToolTip(tooltip);
  }
}

Option::~Option() {}

QPushButton* Option::getButton() { return this->ui.OptionButton; }

void Option::on_OptionButton_clicked() {
  this->current_option->set_current_id(this->id);
}
//-----------------------------------------------------------------------------
