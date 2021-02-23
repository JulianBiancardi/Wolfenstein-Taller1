#ifndef CHAIN_CANNON_ITEM_H
#define CHAIN_CANNON_ITEM_H

#include "item.h"

class ChainCannonItem : public Item {
 public:
  ChainCannonItem(const Point& center, unsigned int id);

  /* Item gets used by the player */
  void use(Player& user) override;

  /* Returns if the player can use the item */
  bool can_be_used_by(const Player& whom) override;
};

#endif
