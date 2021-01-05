#ifndef KEY_H
#define KEY_H

#include "item.h"

class Key : public Item {
 public:
  Key(Point center, int id);
  void use(Player& user) override;
  Item* copy() override;
  bool can_be_used_by(Player& whom) override;
  void remove() override;
};

#endif
