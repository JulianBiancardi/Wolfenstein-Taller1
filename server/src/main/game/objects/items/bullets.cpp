#include "bullets.h"

#include <utility>

#include "../../../../../../common/src/main/ids/map_ids.h"

Bullets::Bullets(const Point& center, int amount, int id)
    : Item(center, id), amount(amount) {}

Bullets::Bullets(const Point& center, int amount)
    : Item(center), amount(amount) {}

void Bullets::use(Player& user) { user.add_bullets(amount); }

bool Bullets::can_be_used_by(const Player& whom) {
  return !whom.is_full_bullets();
}

Item* Bullets::copy() { return new Bullets(position.get_origin(), amount, id); }

Packet Bullets::get_add_item_packet() {
  unsigned char data[ADD_ITEM_SIZE];
  size_t size =
      pack(data, "CICC", ADD_ITEM, id, BULLETS, position.get_origin().getX(),
           position.get_origin().getY());
  return std::move(Packet(size, data));
}