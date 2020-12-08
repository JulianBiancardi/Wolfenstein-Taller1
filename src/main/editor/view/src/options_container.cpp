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
  QList<size_t> ids_section;
  ids_section.append(2);
  ids_section.append(5);
  ids_section.append(1);
  ids_section.append(8);
  ids_section.append(6);
  ids_section.append(4);
  ids_section.append(7);
  ids_section.append(10);
  ids_section.append(11);
  ids_section.append(9);
  ids_section.append(12);

  QGridLayout* gridlayout = new QGridLayout();
  gridlayout->setSpacing(5);
  for (int i = 0; i < ids_section.size(); i++) {
    size_t current_id = ids_section.at(i);
    Option* option = new Option(this, current_id,
                                ids->get_icon_path(current_id), current_option);
    int row = i / this->columns;
    int column = i % this->columns;
    gridlayout->addWidget(option, row, column);
    this->buttongroup.addButton(option->getButton());
  }
  this->ui.scrollAreaWidgetContents->setLayout(gridlayout);
}
