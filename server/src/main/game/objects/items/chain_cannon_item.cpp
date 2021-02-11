#include "chain_cannon_item.h"

#include <utility>

#include "../../../../../../common/src/main/ids/map_ids.h"
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

Packet ChainCannonItem::get_add_item_packet() {
  unsigned char data[ADD_ITEM_SIZE];
  size_t size =
      pack(data, "CICC", ADD_ITEM, id, CHAIN_CANNON,
           position.get_origin().getX(), position.get_origin().getY());
  return std::move(Packet(size, data));
}
