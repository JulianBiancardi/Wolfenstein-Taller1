#ifndef BULLETS_H
#define BULLETS_H

#include "item.h"

class Bullets : public Item {
 public:
  Bullets(Point center, int amount);
  void use(Player& user) override;
  Item* copy() override;
  bool can_be_used_by(Player& whom) override;

 private:
  Bullets(Point center, int amount, int id);
  int amount;
};

#endif
