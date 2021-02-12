#ifndef ITEM_H
#define ITEM_H

#include "../player.h"

class Item {
 private:
 public:
  Item();
  ~Item();

  virtual void use_on(Player& player) = 0;
};

#endif
