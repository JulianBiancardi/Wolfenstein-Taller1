#ifndef CELL_MIMEDATA_H
#define CELL_MIMEDATA_H

#include <QtCore/QMimeData>

#include "../model/include/celd.h"
#include "celd_view.h"

class CellMimeData : public QMimeData {
 private:
  Celd* cell_source;

 public:
  CellMimeData(Celd* cell_source);

  Celd* getcell_source() const;

  ~CellMimeData();
};

CellMimeData::CellMimeData(Celd* cell_source) : cell_source(cell_source) {}

Celd* CellMimeData::getcell_source() const { return this->cell_source; }

CellMimeData::~CellMimeData() {}

#endif /* CELL_MIMEDATA_H */