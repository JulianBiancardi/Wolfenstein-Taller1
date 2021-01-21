#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_OBJECTS_ITEMS_CHEST_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_OBJECTS_ITEMS_CHEST_H_

#include "point_item.h"

class Chest : public PointItem {
 public:
  Chest(const Point& center);
  Item* copy() override;

 private:
  Chest(const Point& center, int id);
};

#endif //WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_OBJECTS_ITEMS_CHEST_H_
