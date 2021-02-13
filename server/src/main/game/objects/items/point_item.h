#ifndef POINT_ITEM_H
#define POINT_ITEM_H

#include "item.h"

class PointItem : public Item {
 private:
  int points_given;

 protected:
  PointItem(const Point& center, unsigned int id, int points_given);

 public:
  /* Item gets used by the player */
  void use(Player& user) override;

  /* Returns if the player can use the item */
  bool can_be_used_by(const Player& whom) override;
};

#endif
