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

  size_t row = 0;
  size_t column = 0;
  size_t counter = 0;

  const QMap<size_t, QMap<QString, QString>>& ids_map = ids->get_ids();
  QMap<size_t, QMap<QString, QString>>::const_iterator iter;
  for (iter = ids_map.begin(); iter != ids_map.end(); iter++) {
    size_t id = iter.key();
    if (ids->get_type(id) == 0) {
      continue;
    }
    Option* option =
        new Option(this, ids->get_type(id), id, ids->get_tooltip(id),
                   ids->get_icon_path(id), current_option);

    row = counter / this->columns;
    column = counter % this->columns;
    gridlayout->addWidget(option, row, column);
    buttongroup.addButton(option->getButton());
    counter++;
  }
}

OptionsContainer::~OptionsContainer() {}
