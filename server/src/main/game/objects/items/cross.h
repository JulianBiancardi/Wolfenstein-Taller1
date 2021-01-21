#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_OBJECTS_ITEMS_CROSS_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_OBJECTS_ITEMS_CROSS_H_

#include "point_item.h"

class Cross : public PointItem {
 public:
  Cross(const Point& center);
  Item* copy() override;

 private:
  Cross(const Point& center, int id);
};

#endif //WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_OBJECTS_ITEMS_CROSS_H_
