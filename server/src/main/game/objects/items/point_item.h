#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_OBJECTS_ITEMS_POINT_ITEM_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_OBJECTS_ITEMS_POINT_ITEM_H_

#include "item.h"

class PointItem : public Item {
 public:
  void use(Player& user) override;
  bool can_be_used_by(Player& whom) override;

 protected:
  PointItem(const Point& center, int points_given);
  PointItem(const Point& center, int points_given, int id);

 private:
  int points_given;
};

#endif //WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_OBJECTS_ITEMS_POINT_ITEM_H_
