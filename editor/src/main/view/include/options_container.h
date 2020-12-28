#ifndef OPTIONS_CONTAINER_H
#define OPTIONS_CONTAINER_H

#include <QtWidgets/QWidget>

#include "QtWidgets/QButtonGroup"
#include "itemsid.h"
#include "option.h"
#include "option_selected.h"
#include "ui_options_container.h"

//------------------------------------------------------------------

class OptionsContainer : public QWidget {
  Q_OBJECT

 public:
  OptionsContainer(QWidget* parent = nullptr, int columns = 2,
                   ItemsId* ids = nullptr,
                   OptionSelected* current_option = nullptr);
  ~OptionsContainer();

 private:
  Ui::OptionContainer ui;
  int columns;
  QButtonGroup buttongroup;

  void addOptions(ItemsId* ids, OptionSelected* current_option);
};

#endif  // OPTIONS_CONTAINER_H
//------------------------------------------------------------------
