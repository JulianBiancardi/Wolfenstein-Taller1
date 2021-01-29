#ifndef MAP_H
#define MAP_H
#include <sys/types.h>

#include <map>

#include "Iobservable.h"
#include "cell.h"

class Map : public IObservable {
 private:
  size_t rows;
  size_t columns;
  size_t offset_row;
  size_t offset_column;
  std::map<int, std::map<int, Cell*>> matrix;

  bool is_in_range(size_t row, size_t column) const;

 public:
  Map(size_t rows = 10, size_t columns = 10);

  Map(const Map&) = delete;              // No copy constructor
  Map& operator=(const Map&) = delete;   // No copy constructor
  Map(Map&& other) = delete;             // Move constructor
  Map& operator=(Map&& other) = delete;  // Move constructor

  size_t row_count() const;
  size_t column_count() const;

  void put(size_t row, size_t column, size_t id, size_t type);
  Cell* at(size_t row, size_t column);
  void clear(size_t row, size_t column);
  void clear_all();

  /*Functions for resize the map*/
  void insert_rowabove(size_t count);
  void insert_rowbelow(size_t count);
  void insert_columnright(size_t count);
  void insert_columnleft(size_t count);
  void remove_rowabove(size_t count);
  void remove_rowbelow(size_t count);
  void remove_columnright(size_t count);
  void remove_columnleft(size_t count);

  void print();  // Debug function

  ~Map();
};

#endif  // MAP_H