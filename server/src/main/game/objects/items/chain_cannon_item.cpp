#include "chain_cannon_item.h"

#include "../../../../common/src/main/ids/gun_ids.h"

ChainCannonItem::ChainCannonItem(Point center) : Item(center) {}

ChainCannonItem::ChainCannonItem(Point center, int id) : Item(center, id) {}

void ChainCannonItem::use(Player& user) { user.add_gun(CHAIN_CANNON_ID); }

Item* ChainCannonItem::copy() {
  return new ChainCannonItem(position.get_origin(), id);
}

bool ChainCannonItem::can_be_used_by(Player& whom) {
  return !whom.has_gun(CHAIN_CANNON_ID);
}
