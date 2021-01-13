#include "options_container.h"

#include "iostream"  //TODO Delete
#include "moc_options_container.cpp"
#include "option.h"

OptionsContainer::OptionsContainer(QWidget* parent, const int columns,
                                   ItemsId* ids, OptionSelected* current_option)
    : QWidget(parent), columns(columns), buttongroup(this) {
  ui.setupUi(this);
  // addOptions(ids, current_option);
}

void OptionsContainer::addOptions(ItemsId* ids,
                                  OptionSelected* current_option) {
  QGridLayout* gridlayout = ui.gridLayout;
  for (size_t i = 1; i < ids->size(); i++) {
    Option* option = new Option(this, i, ids->get_tooltip(i),
                                ids->get_icon_path(i), current_option);
    size_t row = (i - 1) / this->columns;
    size_t column = (i - 1) % this->columns;
    gridlayout->addWidget(option, row, column);
    buttongroup.addButton(option->getButton());
  }
}

OptionsContainer::~OptionsContainer() {}
