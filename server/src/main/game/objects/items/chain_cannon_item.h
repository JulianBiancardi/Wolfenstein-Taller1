#ifndef CHAIN_CANNON_ITEM_H
#define CHAIN_CANNON_ITEM_H

#include "item.h"

class ChainCannonItem : public Item {
 public:
  ChainCannonItem(Point center);
  void use(Player& user) override;
  Item* copy() override;
  bool can_be_used_by(Player& whom) override;
  void remove() override;

 private:
  ChainCannonItem(Point center, int id);
  static int health_recovered;
};

#endif
