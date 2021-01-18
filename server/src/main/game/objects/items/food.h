#ifndef FOOD_H
#define FOOD_H

#include "item.h"

class Food : public Item {
 public:
  Food(Point center);
  void use(Player& user) override;
  Item* copy() override;
  bool can_be_used_by(Player& whom) override;
  void remove() override;

 private:
  Food(Point center, int id);
  int health_recovered;
};

#endif
