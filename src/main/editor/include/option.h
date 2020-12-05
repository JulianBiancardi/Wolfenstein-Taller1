#ifndef OPTION_H
#define OPTION_H

#include <QPushButton>
#include <QWidget>

#include "itemsid.h"
#include "option_selected.h"
#include "ui_option.h"

class Option : public QWidget {
  Q_OBJECT

 public:
  Option(QWidget* parent = nullptr, ssize_t id = -1, ItemsId* ids = nullptr,
         OptionSelected* current_option = nullptr);
  ~Option();

  QPushButton* getButton();

 private slots:

  void on_OptionButton_clicked();

 private:
  Ui::Option ui;
  ssize_t id;
  OptionSelected* current_option;
};

#endif  // OPTION_H
