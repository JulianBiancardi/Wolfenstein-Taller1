#ifndef CELDVIEW_H
#define CELDVIEW_H

#include <QtCore/QDataStream>
#include <QtGui/QDragEnterEvent>
#include <QtGui/QDropEvent>
#include <QtWidgets/QWidget>

#include "../model/include/Iobserver.h"
#include "../model/include/cell.h"
#include "itemsid.h"
#include "option_selected.h"
#include "ui_celdview.h"

class CeldView : public QWidget, public IObserver {
  Q_OBJECT

 private:
  Ui::CeldView ui;
  Cell* celd;
  ItemsId* ids;
  OptionSelected* current_option;

 private slots:
  void on_CeldButton_clicked();

 public:
  explicit CeldView(QWidget* parent = nullptr, Cell* celd = nullptr,
                    ItemsId* ids = nullptr,
                    OptionSelected* current_option = nullptr);

  void mousePressEvent(QMouseEvent* event);
  void mouseMoveEvent(QMouseEvent* event);

  // Evento cuando el drag entra en el widget
  void dragEnterEvent(QDragEnterEvent* event);

  // Evento cuando el drop se realiza en el widget
  void dropEvent(QDropEvent* event);

  ~CeldView();

  void update() override;
};

#endif  // CELDVIEW_H