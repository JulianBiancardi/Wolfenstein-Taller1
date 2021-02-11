#include "crown.h"

#include <utility>

#include "../../../../../../common/src/main/ids/map_ids.h"

Crown::Crown(const Point& center, int id)
    : PointItem(center, CL::crown_points, id) {}

Crown::Crown(const Point& center) : PointItem(center, CL::crown_points) {}

Item* Crown::copy() { return new Crown(position.get_origin(), id); }

Packet Crown::get_add_item_packet() {
  unsigned char data[ADD_ITEM_SIZE];
  size_t size =
      pack(data, "CICC", ADD_ITEM, id, CROWN, position.get_origin().getX(),
           position.get_origin().getY());
  return std::move(Packet(size, data));
}
