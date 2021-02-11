#include "chest.h"

#include <utility>

#include "../../../../../../common/src/main/ids/map_ids.h"

Chest::Chest(const Point& center, int id)
    : PointItem(center, CL::chests_points, id) {}

Chest::Chest(const Point& center) : PointItem(center, CL::chests_points) {}

Item* Chest::copy() { return new Chest(position.get_origin(), id); }

Packet Chest::get_add_item_packet() {
  unsigned char data[ADD_ITEM_SIZE];
  size_t size =
      pack(data, "CICC", ADD_ITEM, id, CHEST, position.get_origin().getX(),
           position.get_origin().getY());
  return std::move(Packet(size, data));
}
