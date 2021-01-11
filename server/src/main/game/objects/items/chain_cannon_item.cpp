#include "chain_cannon_item.h"

// TODO No need to use the actual object, a number is enough on server-side
//#include "../../../../common/src/main/guns/chain_cannon.h"

ChainCannonItem::ChainCannonItem(Point center, int id) : Item(center, id) {}

void ChainCannonItem::use(Player& user) {
  // user.add_gun(gun);
}

Item* ChainCannonItem::copy() {
  return new ChainCannonItem(position.get_origin(), id);
}

bool ChainCannonItem::can_be_used_by(Player& whom) {
  // return !whom.has_gun(gun);
  return false;
}

void ChainCannonItem::remove() {}
