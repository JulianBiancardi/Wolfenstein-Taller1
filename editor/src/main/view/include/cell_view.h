#ifndef CELLVIEW_H
#define CELLVIEW_H

#include <QtGui/QDragEnterEvent>
#include <QtGui/QDropEvent>
#include <QtWidgets/QWidget>

#include "../model/include/Iobserver.h"
#include "../model/include/cell.h"
#include "itemsid.h"
#include "option_selected.h"
#include "ui_cellview.h"

class CellView : public QWidget, public IObserver {
  Q_OBJECT

 private:
  Ui::CellView ui;
  Cell* cell;
  ItemsId* ids;
  OptionSelected* current_option;

 private slots:
  void on_CeldButton_clicked();

 public:
  CellView(QWidget* parent = nullptr, Cell* cell = nullptr,
           ItemsId* ids = nullptr, OptionSelected* current_option = nullptr);

  void mousePressEvent(QMouseEvent* event);
  void mouseMoveEvent(QMouseEvent* event);

  // Evento cuando el drag entra en el widget
  void dragEnterEvent(QDragEnterEvent* event);

  // Evento cuando el drop se realiza en el widget
  void dropEvent(QDropEvent* event);

  ~CellView();

  void update() override;
};

#endif  // CELLVIEW_H