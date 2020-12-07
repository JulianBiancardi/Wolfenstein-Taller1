#ifndef CELDVIEW_H
#define CELDVIEW_H

#include <QtWidgets/QWidget>

#include "../model/include/Iobserver.h"
#include "../model/include/celd.h"
#include "itemsid.h"
#include "option_selected.h"
#include "ui_celdview.h"

static Celd df_celd;
static ItemsId df_ids;
static OptionSelected df_option;

class CeldView : public QWidget, public IObserver {
  Q_OBJECT

 public:
  explicit CeldView(QWidget* parent = nullptr, Celd& celd = df_celd,
                    ItemsId& ids = df_ids,
                    OptionSelected& current_option = df_option);
  ~CeldView();

  void update() override;

 private slots:
  void on_CeldButton_clicked();

 private:
  Ui::CeldView ui;
  Celd& celd;
  ItemsId& ids;
  OptionSelected& current_option;
};

#endif  // CELDVIEW_H