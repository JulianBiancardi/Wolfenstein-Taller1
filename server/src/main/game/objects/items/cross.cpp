#include "cross.h"

#include <utility>

#include "../../../../../../common/src/main/ids/map_ids.h"

Cross::Cross(const Point& center, int id)
    : PointItem(center, CL::crosses_points, id) {}

Cross::Cross(const Point& center) : PointItem(center, CL::crosses_points) {}

Item* Cross::copy() { return new Cross(position.get_origin(), id); }

Packet Cross::get_add_item_packet() {
  unsigned char data[ADD_ITEM_SIZE];
  size_t size =
      pack(data, "CICC", ADD_ITEM, id, CROSS, position.get_origin().getX(),
           position.get_origin().getY());
  return std::move(Packet(size, data));
}
