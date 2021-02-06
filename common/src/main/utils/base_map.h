#ifndef BASE_MAP_H
#define BASE_MAP_H

#include <string>

#include "matrix.h"
#include "point.h"

#define MAP_NAME_MAX_SIZE 64

class BaseMap {
 private:
  Matrix<int> map_matrix;

 protected:
  std::string map_name;
  unsigned char player_capacity;

  void load_map_matrix();
  void load_capacity();

 public:
  BaseMap(Matrix<int>& map_matrix);
  BaseMap(const std::string& map_name);
  ~BaseMap();

  /* Returns the name of the map */
  const std::string& get_name() const;

  /* Returns the player capacity */
  unsigned char get_capacity() const;

  /* Returns true if the point x,y is a wall, false otherwise. */
  bool is_wall(size_t x, size_t y);

  /* Returns a copy of the value in the point x,y. */
  int operator()(size_t x, size_t y);

  /* Returns the amount of rows in the matrix. */
  size_t get_rows();

/* Returns the amount of columns in the matrix. */
  size_t get_columns();

};

#endif