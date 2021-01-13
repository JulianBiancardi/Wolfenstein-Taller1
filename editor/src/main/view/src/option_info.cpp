#include "option_info.h"

#include <QtCore/QString>

#include "moc_option_info.cpp"

OptionInfo::OptionInfo(QWidget* parent, OptionSelected* current_option)
    : QWidget(parent), current_option(current_option) {
  ui.setupUi(this);
}

void OptionInfo::init(OptionSelected* current_option) {
  // TODO DELETE
  this->current_option = current_option;
  current_option->add_observer(this);
}

void OptionInfo::update() {
  size_t id = current_option->get_current_id();
  ui.Id->setText(QString("Id: %1").arg(id));

  QString name = "Name: " + current_option->get_current_name();
  ui.Name->setText(name);

  QPixmap pixmap(current_option->get_current_icon());
  ui.Icon->setPixmap(pixmap);
  ui.Icon->setScaledContents(true);
}

OptionInfo::~OptionInfo() {}
