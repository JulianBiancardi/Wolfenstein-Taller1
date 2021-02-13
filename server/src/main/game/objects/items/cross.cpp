#include "cross.h"

#include <utility>

#include "../../../../../../common/src/main/ids/map_ids.h"

Cross::Cross(const Point& center, int id)
    : PointItem(center, CL::cross_points, id) {}

Cross::Cross(const Point& center) : PointItem(center, CL::cross_points) {}

Item* Cross::copy() { return new Cross(position.get_origin(), id); }

Packet Cross::get_add_item_packet() {
  unsigned char data[ADD_ITEM_SIZE];
  size_t size = pack(data, "CICCC", ADD_ITEM, id, CROSS,
                     (int)position.get_origin().getX(),
                     (int)position.get_origin().getY());
  return std::move(Packet(size, data));
}
