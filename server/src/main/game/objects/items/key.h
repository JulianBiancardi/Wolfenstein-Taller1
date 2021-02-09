#ifndef KEY_H
#define KEY_H

#include "item.h"

class Key : public Item {
 private:
  Key(const Point& center, int id);

 public:
  explicit Key(const Point& center);

  /* Item gets used by the player */
  void use(Player& user) override;

  /* Returns if the player can use the item */
  bool can_be_used_by(const Player& whom) override;

  /* Returns a copy of the element */
  Item* copy() override;
};

#endif
