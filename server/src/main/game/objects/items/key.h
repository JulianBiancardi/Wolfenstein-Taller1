#ifndef KEY_H
#define KEY_H

#include "item.h"

class Key : public Item {
 private:
  Key(Point center, int id);

 public:
  Key(Point center);
  void use(Player& user) override;
  Item* copy() override;
  bool can_be_used_by(Player& whom) override;
  void remove() override;
};

#endif
