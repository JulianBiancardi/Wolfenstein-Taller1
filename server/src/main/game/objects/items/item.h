#ifndef ITEMS_H
#define ITEMS_H

#include "../../player.h"
#include "../object.h"

class Item : public Object {
 protected:
  Item(const Point& center, int id);

 public:
  explicit Item(const Point& center);
  ~Item() override;

  /* Item gets used by the player */
  virtual void use(Player& user) = 0;

  /* Returns if the player can use the item */
  virtual bool can_be_used_by(const Player& whom) = 0;

  /* Returns a copy of the element */
  virtual Item* copy() = 0;  // Deep copying
};

#endif
