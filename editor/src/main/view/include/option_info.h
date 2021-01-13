#ifndef OPTION_INFO_H
#define OPTION_INFO_H

#include <Iobserver.h>
#include <option_selected.h>

#include <QtWidgets/QWidget>

#include "ui_option_info.h"

class OptionInfo : public QWidget, public IObserver {
  Q_OBJECT

 private:
  Ui::OptionInfo ui;
  OptionSelected* current_option;

 public:
  OptionInfo(QWidget* parent = nullptr,
             OptionSelected* current_option = nullptr);

  void init(OptionSelected* current_option);

  void update() override;

  ~OptionInfo();
};

#endif  // OPTION_INFO_H