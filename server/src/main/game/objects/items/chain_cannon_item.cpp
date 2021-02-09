#include "chain_cannon_item.h"

#include "../../../../common/src/main/ids/gun_ids.h"

ChainCannonItem::ChainCannonItem(const Point& center, int id)
    : Item(center, id) {}

ChainCannonItem::ChainCannonItem(const Point& center) : Item(center) {}

void ChainCannonItem::use(Player& user) { user.add_gun(CHAIN_CANNON_ID); }

bool ChainCannonItem::can_be_used_by(const Player& whom) {
  return !whom.has_gun(CHAIN_CANNON_ID);
}

Item* ChainCannonItem::copy() {
  return new ChainCannonItem(position.get_origin(), id);
}
