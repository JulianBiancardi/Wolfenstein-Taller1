#ifndef CELDVIEW_H
#define CELDVIEW_H

#include <QtWidgets/QWidget>

#include "../model/include/Iobserver.h"
#include "../model/include/celd.h"
#include "itemsid.h"
#include "option_selected.h"
#include "ui_celdview.h"

class CeldView : public QWidget, public IObserver {
  Q_OBJECT

 private:
  Ui::CeldView ui;
  Celd* celd;
  ItemsId* ids;
  OptionSelected* current_option;

 private slots:
  void on_CeldButton_clicked();

 public:
  explicit CeldView(QWidget* parent = nullptr, Celd* celd = nullptr,
                    ItemsId* ids = nullptr,
                    OptionSelected* current_option = nullptr);
  ~CeldView();

  void update() override;
};

#endif  // CELDVIEW_H