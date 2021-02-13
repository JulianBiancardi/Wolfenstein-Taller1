#include "bullets.h"

#include <utility>

#include "../../../../../../common/src/main/ids/map_ids.h"

Bullets::Bullets(const Point& center, int amount, unsigned int id)
    : Item(center, id), amount(amount) {}

void Bullets::use(Player& user) { user.add_bullets(amount); }

bool Bullets::can_be_used_by(const Player& whom) {
  return !whom.is_full_bullets();
}

Item* Bullets::copy() { return new Bullets(position.get_origin(), amount, id); }

Packet Bullets::get_add_item_packet() {
  unsigned char data[ADD_ITEM_SIZE];
  size_t size = pack(data, "CICCC", ADD_ITEM, id, BULLETS,
                     (int) position.get_origin().getX(),
                     (int) position.get_origin().getY());
  return std::move(Packet(size, data));
}