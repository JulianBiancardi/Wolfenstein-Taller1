#include "key.h"

#include <utility>

#include "../../../../../../common/src/main/ids/map_ids.h"

Key::Key(const Point& center, int id) : Item(center, id) {}

Key::Key(const Point& center) : Item(center) {}

void Key::use(Player& user) { user.add_key(); }

bool Key::can_be_used_by(const Player& whom) { return true; }

Item* Key::copy() { return new Key(position.get_origin(), id); }

Packet Key::get_add_item_packet() {
  unsigned char data[ADD_ITEM_SIZE];
  size_t size =
      pack(data, "CICC", ADD_ITEM, id, KEY, position.get_origin().getX(),
           position.get_origin().getY());
  return std::move(Packet(size, data));
}
