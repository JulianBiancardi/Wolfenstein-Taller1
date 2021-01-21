#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_OBJECTS_ITEMS_CUP_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_OBJECTS_ITEMS_CUP_H_

#include "point_item.h"

class Cup : public PointItem {
 public:
  Cup(const Point& center);
  Item* copy() override;

 private:
  Cup(const Point& center, int id);
};

#endif //WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_OBJECTS_ITEMS_CUP_H_
