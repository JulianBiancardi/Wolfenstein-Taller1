#ifndef CELLVIEW_H
#define CELLVIEW_H

#include <QtGui/QDragEnterEvent>
#include <QtGui/QDropEvent>
#include <QtWidgets/QUndoStack>
#include <QtWidgets/QWidget>

#include "../../model/include/Iobserver.h"
#include "../../model/include/cell.h"
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
  QUndoStack* undostack;

 public:
  CellView(QWidget* parent = nullptr, Cell* cell = nullptr,
           ItemsId* ids = nullptr, OptionSelected* current_option = nullptr,
           QUndoStack* undostack = nullptr);

  void update() override;

  // Evento cuando el drag entra en el widget
  void dragEnterEvent(QDragEnterEvent* event);
  // Evento cuando el drop se realiza en el widget
  void dropEvent(QDropEvent* event);

  void handleMousePressEvent(QMouseEvent* event);
  void handleMouseMoveEventInsidePaint(QMouseEvent* event);
  void handleMouseMoveEventInsideClear(QMouseEvent* event);
  void handleMouseMoveEventInsideDrag(QMouseEvent* event);

  ~CellView();
};

#endif  // CELLVIEW_H