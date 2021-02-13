#include "chest.h"

#include <utility>

#include "../../../../../../common/src/main/ids/map_ids.h"

Chest::Chest(const Point& center, unsigned int id)
    : PointItem(center, id, CL::chest_points) {}

Item* Chest::copy() { return new Chest(position.get_origin(), id); }

Packet Chest::get_add_item_packet() {
  unsigned char data[ADD_ITEM_SIZE];
  size_t size = pack(data, "CICCC", ADD_ITEM, id, CHEST,
                     (int) position.get_origin().getX(),
                     (int) position.get_origin().getY());
  return std::move(Packet(size, data));
}
