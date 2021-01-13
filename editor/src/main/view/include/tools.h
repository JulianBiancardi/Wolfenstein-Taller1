#ifndef TOOLS_H
#define TOOLS_H

#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QWidget>

#include "mapgrid.h"
#include "ui_tools.h"
//------------------------------------------------------------------

class Tools : public QWidget {
  Q_OBJECT

 private:
  Ui::Tools ui;
  QButtonGroup buttongroup;
  MapGrid* mapgrid;
  size_t rows;
  size_t columns;

 public:
  Tools(QWidget* parent = nullptr);

  void init(ItemsId* ids, OptionSelected* current_option, MapGrid* mapgrid);

  ~Tools();

 private slots:
  void on_EditButton_clicked();
  void on_ResizeButton_clicked();
  void on_ClearAllButton_clicked();
  void on_spinBoxHeight_valueChanged(int value);
  void on_spinBoxHeight_editingFinished();
  void on_spinBoxWidth_valueChanged(int value);
  void on_spinBoxWidth_editingFinished();

  void on_InsertRowAbove_clicked();
  void on_InsertRowBelow_clicked();
  void on_InsertColumnLeft_clicked();
  void on_InsertColumnRight_clicked();
  void on_RemoveRowAbove_clicked();
  void on_RemoveRowBelow_clicked();
  void on_RemoveColumnLeft_clicked();
  void on_RemoveColumnRight_clicked();
};

#endif  // TOOLS_H
//------------------------------------------------------------------
