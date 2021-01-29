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
  for (size_t id = 1; id < ids->size(); id++) {
    Option* option =
        new Option(this, ids->get_type(id), id, ids->get_tooltip(id),
                   ids->get_icon_path(id), current_option);
    size_t row = (id - 1) / this->columns;
    size_t column = (id - 1) % this->columns;
    gridlayout->addWidget(option, row, column);
    buttongroup.addButton(option->getButton());
  }
}

OptionsContainer::~OptionsContainer() {}
