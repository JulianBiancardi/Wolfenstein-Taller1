#ifndef CELL_MIMEDATA_H
#define CELL_MIMEDATA_H

#include <QtCore/QMimeData>

#include "../model/include/cell.h"

class CellMimeData : public QMimeData {
 private:
  Cell* cell_source;

 public:
  CellMimeData(Cell* cell_source);

  Cell* getcell_source() const;

  ~CellMimeData();
};

CellMimeData::CellMimeData(Cell* cell_source) : cell_source(cell_source) {}

Cell* CellMimeData::getcell_source() const { return this->cell_source; }

CellMimeData::~CellMimeData() {}

#endif /* CELL_MIMEDATA_H */