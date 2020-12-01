#ifndef WOLFENSTEIN_TALLER1_MAP_H
#define WOLFENSTEIN_TALLER1_MAP_H

#include "../../matrix.h"
#include "../../point.h"

class Map {
 private:
  Matrix<int> expanded_map;

 public:
  Map();
  ~Map() { }

  static Map& get_map();
  bool can_move_to(Point destiny);
};

#endif //WOLFENSTEIN_TALLER1_MAP_H
