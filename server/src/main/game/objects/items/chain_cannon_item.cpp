#include "chain_cannon_item.h"

#include "../../../../common/src/main/ids/gun_ids.h"

ChainCannonItem::ChainCannonItem(const Point& center, unsigned int id)
    : Item(center, id) {}

void ChainCannonItem::use(Player& user) { user.add_gun(CHAIN_CANNON_ID); }

bool ChainCannonItem::can_be_used_by(const Player& whom) {
  return !whom.has_gun(CHAIN_CANNON_ID);
}
