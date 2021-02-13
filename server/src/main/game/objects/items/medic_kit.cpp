#include "medic_kit.h"

#include <utility>

#include "../../../../../../common/src/main/ids/map_ids.h"

MedicKit::MedicKit(const Point& center, unsigned int id)
    : Item(center, id), health_recovered(CL::medic_kit_health_recovered) {}

void MedicKit::use(Player& user) { user.add_health(health_recovered); }

bool MedicKit::can_be_used_by(const Player& whom) {
  return !whom.is_full_health();
}

Item* MedicKit::copy() { return new MedicKit(position.get_origin(), id); }

Packet MedicKit::get_add_item_packet() {
  unsigned char data[ADD_ITEM_SIZE];
  size_t size = pack(data, "CICCC", ADD_ITEM, id, MEDKIT,
                     (int) position.get_origin().getX(),
                     (int) position.get_origin().getY());
  return std::move(Packet(size, data));
}
