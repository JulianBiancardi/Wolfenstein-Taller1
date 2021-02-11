#include "medic_kit.h"

#include <utility>

#include "../../../../../../common/src/main/ids/map_ids.h"

MedicKit::MedicKit(const Point& center, int id) : Item(center, id) {
  health_recovered = ConfigLoader::medic_kit_health_recovered;
}

MedicKit::MedicKit(const Point& center) : Item(center) {
  health_recovered = ConfigLoader::medic_kit_health_recovered;
}

void MedicKit::use(Player& user) { user.add_health(health_recovered); }

bool MedicKit::can_be_used_by(const Player& whom) {
  return !whom.is_full_health();
}

Item* MedicKit::copy() { return new MedicKit(position.get_origin(), id); }

Packet MedicKit::get_add_item_packet() {
  unsigned char data[ADD_ITEM_SIZE];
  size_t size =
      pack(data, "CICC", ADD_ITEM, id, MEDKIT, position.get_origin().getX(),
           position.get_origin().getY());
  return std::move(Packet(size, data));
}
