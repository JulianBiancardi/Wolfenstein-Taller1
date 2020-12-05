#ifndef CELD_H
#define CELD_H

#include <QWidget>

#include "itemsid.h"
#include "option_selected.h"
#include "ui_celd.h"

class Celd : public QWidget {
  Q_OBJECT

 public:
  explicit Celd(QWidget* parent = nullptr, ItemsId* ids = nullptr,
                OptionSelected* current_option = nullptr);
  ~Celd();

 private slots:
  void on_CeldButton_clicked();

  void on_CeldButton_pressed();

 private:
  Ui::Celd ui;
  ItemsId* ids;
  OptionSelected* current_option;
};

#endif  // CELD_H
