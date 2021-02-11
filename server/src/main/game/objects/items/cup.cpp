#include "cup.h"

#include <utility>

#include "../../../../../../common/src/main/ids/map_ids.h"

Cup::Cup(const Point& center, int id) : PointItem(center, CL::cup_points, id) {}

Cup::Cup(const Point& center) : PointItem(center, CL::cup_points) {}

Item* Cup::copy() { return new Cup(position.get_origin(), id); }

Packet Cup::get_add_item_packet() {
  unsigned char data[ADD_ITEM_SIZE];
  size_t size =
      pack(data, "CICCC", ADD_ITEM, id, CUP, (int)position.get_origin().getX(),
           (int)position.get_origin().getY());
  return std::move(Packet(size, data));
}
