#ifndef WOLFENSTEIN_TALLER1_FOOD_H
#define WOLFENSTEIN_TALLER1_FOOD_H

#include "items.h"

class Food : public Items {
 public:
  Food(Point center, int id);
  void use(Player &user) override;
  Items *copy() override;
  bool can_be_used_by(Player &whom) override;
  void remove() override;

 private:
  int health_recovered;
};

#endif //WOLFENSTEIN_TALLER1_FOOD_H
