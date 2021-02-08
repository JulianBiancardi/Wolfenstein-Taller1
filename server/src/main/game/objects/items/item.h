#ifndef ITEMS_H
#define ITEMS_H

#include "../../player.h"
#include "../object.h"

class Item : public Object {
 protected:
  Item(Point center, int id);

 public:
  Item(Point center);
  ~Item();

  virtual void use(Player& user) = 0;
  virtual bool can_be_used_by(Player& whom) = 0;
  virtual Item* copy() = 0;  // Deep copying
};

#endif
