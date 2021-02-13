#ifndef CHAIN_CANNON_ITEM_H
#define CHAIN_CANNON_ITEM_H

#include "item.h"

class ChainCannonItem : public Item {
 private:
 public:
  ChainCannonItem(const Ray& position, unsigned int resource_id,
                  unsigned int id);
  ~ChainCannonItem();

  void use_on(Player& player);
};

#endif
