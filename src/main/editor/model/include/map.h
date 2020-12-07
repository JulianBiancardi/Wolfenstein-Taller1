#ifndef MAP_H
#define MAP_H
#include <sys/types.h>

#include <vector>

#include "celd.h"

class Map {
 private:
  size_t rows;
  size_t columns;
  std::vector<std::vector<Celd>> matrix;

  bool is_in_range(size_t row, size_t column) const;

 public:
  Map(size_t rows = 5, size_t columns = 5);

  size_t row_count() const;
  size_t column_count() const;

  void put(size_t row, size_t column, size_t id);
  Celd* at(size_t row, size_t column);
  void clear(size_t row, size_t column);
  void clear_all();

  void resize(size_t new_rows, size_t new_columns);

  ~Map();
};

#endif  // MAP_H