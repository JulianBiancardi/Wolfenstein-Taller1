#include "tools.h"

#include <QtWidgets/QGraphicsDropShadowEffect>
#include <stdexcept>  //Runtime error

#include "iostream"  //TODO DELETE
#include "moc_tools.cpp"
#include "options_container.h"

#define OPTION_CONTAINER_PAGE 0
#define RESIZE_PAGE 1
#define PAINT_STATE 1
#define DRAG_STATE 2

Tools::Tools(QWidget* parent) : QWidget(parent) {
  ui.setupUi(this);
  ui.stackedWidget->setCurrentIndex(OPTION_CONTAINER_PAGE);

  QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
  shadowEffect->setColor(QColor(0, 0, 0, 255 * 0.3));
  shadowEffect->setXOffset(-4);
  shadowEffect->setYOffset(0);
  shadowEffect->setBlurRadius(12);
  setGraphicsEffect(shadowEffect);

  tools_buttongroup.addButton(ui.EditButton);
  tools_buttongroup.addButton(ui.ResizeButton);

  edit_buttongroup.addButton(ui.PaintButton);
  edit_buttongroup.addButton(ui.DragButton);
}

void Tools::init(ItemsId* ids, OptionSelected* current_option,
                 MapGrid* mapgrid) {
  if (mapgrid == nullptr || current_option == nullptr) {
    throw std::runtime_error("Error to create ToolsWidget");
  }
  this->mapgrid = mapgrid;
  this->current_option = current_option;
  rows = mapgrid->rowscount();
  columns = mapgrid->columnscount();

  ui.OptionsContainerWidget->addOptions(ids,
                                        current_option);  // TODO CHANGE THIS
  ui.OptionInfoWidget->init(current_option);
  ui.spinBoxHeight->setValue(rows);
  ui.spinBoxWidth->setValue(columns);
}

void Tools::on_EditButton_clicked() {
  ui.stackedWidget->setCurrentIndex(OPTION_CONTAINER_PAGE);
}
void Tools::on_ResizeButton_clicked() {
  ui.stackedWidget->setCurrentIndex(RESIZE_PAGE);
}

void Tools::on_PaintButton_clicked() {
  current_option->change_state(PAINT_STATE);
}
void Tools::on_DragButton_clicked() {
  current_option->change_state(DRAG_STATE);
}
void Tools::on_ClearAllButton_clicked() { mapgrid->clear(); }

void Tools::on_spinBoxHeight_valueChanged(int value) { rows = value; }
void Tools::on_spinBoxHeight_editingFinished() {
  size_t rowscount = mapgrid->rowscount();
  if (rows == rowscount) {
    return;
  }
  if (rows > rowscount) {
    mapgrid->insert_rowbelow(rows - rowscount);
  } else {
    mapgrid->remove_rowbelow(rowscount - rows);
  }
}
void Tools::on_spinBoxWidth_valueChanged(int value) { columns = value; }
void Tools::on_spinBoxWidth_editingFinished() {
  size_t columnscount = mapgrid->columnscount();
  if (columns == columnscount) {
    return;
  }
  if (columns > columnscount) {
    mapgrid->insert_columnright(columns - columnscount);
  } else {
    mapgrid->remove_columnright(columnscount - columns);
  }
}

void Tools::on_InsertRowAbove_clicked() { mapgrid->insert_rowabove(1); }
void Tools::on_InsertRowBelow_clicked() { mapgrid->insert_rowbelow(1); }
void Tools::on_InsertColumnLeft_clicked() { mapgrid->insert_columnleft(1); }
void Tools::on_InsertColumnRight_clicked() { mapgrid->insert_columnright(1); }
void Tools::on_RemoveRowAbove_clicked() { mapgrid->remove_rowabove(1); }
void Tools::on_RemoveRowBelow_clicked() { mapgrid->remove_rowbelow(1); }
void Tools::on_RemoveColumnLeft_clicked() { mapgrid->remove_columnleft(1); }
void Tools::on_RemoveColumnRight_clicked() { mapgrid->remove_columnright(1); }

Tools::~Tools() {}
