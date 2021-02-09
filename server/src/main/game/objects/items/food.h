#ifndef FOOD_H
#define FOOD_H

#include "item.h"

class Food : public Item {
 private:
  Food(const Point& center, int id);
  int health_recovered;

 public:
  explicit Food(const Point& center);

  /* Item gets used by the player */
  void use(Player& user) override;

  /* Returns if the player can use the item */
  bool can_be_used_by(const Player& whom) override;

  /* Returns a copy of the element */
  Item* copy() override;
};

#endif
