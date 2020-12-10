#include "options_container.h"

#include "iostream"
#include "option.h"

// Incluyo el archivo creado por el moc para que cmake lo detecte y compile
#include "moc_options_container.cpp"

OptionsContainer::OptionsContainer(QWidget* parent, const int columns,
                                   ItemsId* ids, OptionSelected* current_option)
    : QWidget(parent), columns(columns), buttongroup(this) {
  this->ui.setupUi(this);
  addOptions(ids, current_option);
}

OptionsContainer::~OptionsContainer() {}

void OptionsContainer::addOptions(ItemsId* ids,
                                  OptionSelected* current_option) {
  QGridLayout* gridlayout = new QGridLayout();
  gridlayout->setSpacing(5);
  for (size_t i = 0; i < ids->size(); i++) {
    Option* option = new Option(this, i, ids->get_tooltip(i),
                                ids->get_icon_path(i), current_option);
    size_t row = i / this->columns;
    size_t column = i % this->columns;
    gridlayout->addWidget(option, row, column);
    this->buttongroup.addButton(option->getButton());
  }
  this->ui.scrollAreaWidgetContents->setLayout(gridlayout);
}
