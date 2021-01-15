#ifndef ITEMS_H
#define ITEMS_H

#include "../../../../../../common/src/main/object.h"
#include "../../player.h"

class Item : public Object {
 public:
  Item(Point center, int id);
  ~Item();

  virtual void use(Player& user) = 0;
  virtual bool can_be_used_by(Player& whom) = 0;
  virtual Item* copy() = 0;  // Deep copying
  virtual void remove() = 0;
};

#endif
