#ifndef FOOD_H
#define FOOD_H

#include "item.h"

class Food : public Item {
 private:
 public:
  Food(const Ray& position, unsigned int resource_id, unsigned int id);
  ~Food();

  void use_on(Player& player);
};

#endif
