#ifndef BULLETS_H
#define BULLETS_H

#include "item.h"

class Bullets : public Item {
 private:
  Bullets(const Point& center, int amount, int id);
  int amount;

 public:
  Bullets(const Point& center, int amount);

  /* Item gets used by the player */
  void use(Player& user) override;

  /* Returns if the player can use the item */
  bool can_be_used_by(const Player& whom) override;

  /* Returns a copy of the element */
  Item* copy() override;
};

#endif
