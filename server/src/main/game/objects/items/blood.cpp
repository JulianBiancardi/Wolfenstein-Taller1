#include "blood.h"

#include <utility>

#include "../../../../../../common/src/main/ids/map_ids.h"

Blood::Blood(const Point& center, unsigned int id)
    : Item(center, id),
      health_recovered(CL::blood_health_recovered),
      less_than(CL::blood_health_recovered_if_less_than) {}

void Blood::use(Player& user) { user.add_health(health_recovered); }

bool Blood::can_be_used_by(const Player& whom) {
  return whom.get_health() < less_than;
}

Item* Blood::copy() { return new Blood(position.get_origin(), id); }

Packet Blood::get_add_item_packet() {
  unsigned char data[ADD_ITEM_SIZE];
  size_t size = pack(data, "CICCC", ADD_ITEM, id, BLOOD,
                     (int) position.get_origin().getX(),
                     (int) position.get_origin().getY());
  return std::move(Packet(size, data));
}