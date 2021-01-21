#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_OBJECTS_ITEMS_CROWN_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_OBJECTS_ITEMS_CROWN_H_

#include "point_item.h"

class Crown : public PointItem {
 public:
  Crown(const Point& center);
  Item* copy() override;

 private:
  Crown(const Point& center, int id);
};

#endif //WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_OBJECTS_ITEMS_CROWN_H_
