#include "map.h"

#include <algorithm>

bool Map::is_in_range(size_t row, size_t column) const {
  return (row < this->rows && column < this->columns);
}

Map::Map(size_t rows, size_t columns) : rows(rows), columns(columns) {
  matrix.resize(columns, std::vector<Celd>(rows));
}

size_t Map::row_count() const { return this->rows; }
size_t Map::column_count() const { return this->columns; }

void Map::put(size_t row, size_t column, size_t id) {
  if (!is_in_range(row, column)) {
    return;  // TODO error
  }
  Celd& celd = matrix[row][column];
  if (!celd.is_empty()) {
    return;  // TODO celd no empty
  }
  celd.set_id(id);
}

Celd* Map::at(size_t row, size_t column) {
  /*
  if (!is_in_range(row, column)) {
    return nullptr;  // TODO error
  }*/
  return &matrix[row][column];
}

void Map::clear(size_t row, size_t column) {
  if (!is_in_range(row, column)) {
    return;  // TODO error
  }
  matrix[row][column].clear();
}

void Map::clear_all() {
  for (size_t row = 0; row < this->rows; row++) {
    for (size_t column = 0; column < this->columns; column++) {
      matrix[row][column].clear();
    }
  }
}

void Map::resize(size_t new_rows, size_t new_columns) {
  if (new_rows == this->rows && new_columns == this->columns) {
    return;
  }
}

Map::~Map() {}
