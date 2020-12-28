#include "include/map.h"

#include <algorithm>

#include "iostream"

#define BASE_ID 0
#define ERROR 0
//----------------------------------------------------------------
bool Map::is_in_range(size_t row, size_t column) const {
  return (row < rows && column < columns);
}

Map::Map(size_t rows, size_t columns) : rows(rows), columns(columns) {
  for (size_t row = 0; row < rows; row++) {
    for (size_t column = 0; column < columns; column++) {
      matrix[row][column] = new Cell();
    }
  }
  offset_row = 0;
  offset_column = 0;
}

Map& Map::operator=(Map&& other) { return other; }

size_t Map::row_count() const { return rows; }

size_t Map::column_count() const { return columns; }

void Map::put(size_t row, size_t column, size_t id) {
  if (!is_in_range(row, column)) {
    return;  // TODO error
  }
  this->matrix[row + this->offset_row][column + this->offset_column]->set_id(
      id);
}

Cell* Map::at(size_t row, size_t column) {
  if (!is_in_range(row, column)) {
    return nullptr;  // TODO error
  }
  return matrix[row + offset_row][column + offset_column];
}

void Map::clear(size_t row, size_t column) {
  if (!is_in_range(row, column)) {
    return;  // TODO error
  }
  put(row, column, BASE_ID);
}

void Map::clear_all() {
  for (size_t row = 0; row < rows; row++) {
    for (size_t column = 0; column < columns; column++) {
      put(row, column, BASE_ID);
    }
  }
}

void Map::insert_rowabove() {
  offset_row--;
  int last_column = columns + offset_column;  // TODO see this
  for (int column = offset_column; column < last_column; column++) {
    matrix[offset_row][column] = new Cell();
  }
  rows++;
}

void Map::insert_rowbelow() {
  int new_row = rows + offset_row;
  int last_column = columns + offset_column;
  for (int column = offset_column; column < last_column; column++) {
    matrix[new_row][column] = new Cell();
  }
  rows++;
}

void Map::insert_columnleft() {
  offset_column--;
  std::map<int, std::map<int, Cell*>>::iterator it;
  for (it = matrix.begin(); it != matrix.end(); it++) {
    it->second[offset_column] = new Cell();
  }
  columns++;
}

void Map::insert_columnright() {
  int new_column = columns + offset_column;

  std::map<int, std::map<int, Cell*>>::iterator it;
  for (it = matrix.begin(); it != matrix.end(); it++) {
    it->second[new_column] = new Cell();
  }
  columns++;
}

void Map::remove_rowabove() {
  if (rows == 0) {
    return;
  }
  std::map<int, Cell*>::iterator it;
  for (it = matrix[offset_row].begin(); it != matrix[offset_row].end(); it++) {
    delete it->second;
  }
  matrix.erase(offset_row);
  offset_row++;
  rows--;
}

void Map::remove_rowbelow() {
  if (rows == 0) {
    return;
  }
  int last_row = (rows + offset_row) - 1;
  std::map<int, Cell*>::iterator it;
  for (it = matrix[last_row].begin(); it != matrix[last_row].end(); it++) {
    delete it->second;
  }
  matrix.erase(last_row);
  rows--;
}

void Map::remove_columnright() {
  if (columns == 0) {
    return;
  }
  std::map<int, std::map<int, Cell*>>::iterator it;
  for (it = matrix.begin(); it != matrix.end(); it++) {
    delete it->second[offset_column];
  }
  offset_column++;
  columns--;
}

void Map::remove_columnleft() {
  if (columns == 0) {
    return;
  }
  int last_column = (columns + offset_column) - 1;
  std::map<int, std::map<int, Cell*>>::iterator it;
  for (it = matrix.begin(); it != matrix.end(); it++) {
    delete it->second[last_column];
  }
  columns--;
}

void Map::print() {
  for (size_t row = 0; row < this->rows; row++) {
    for (size_t column = 0; column < this->columns; column++) {
      if (at(row, column) == nullptr) {
        std::cout << "\n Invalid Cell" << row << " " << column << std::endl;
      } else {
        std::cout << at(row, column)->get_id() << " ";
      }
    }
    std::cout << std::endl;
  }
}

Map::~Map() {
  for (size_t row = 0; row < rows; row++) {
    for (size_t column = 0; column < columns; column++) {
      if (at(row, column) == nullptr) {
      } else {
        delete at(row, column);
      }
    }
  }
}
