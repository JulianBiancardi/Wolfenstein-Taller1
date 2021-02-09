#include "medic_kit.h"

MedicKit::MedicKit(const Point& center, int id) : Item(center, id) {
  health_recovered = ConfigLoader::medic_kit_health_recovered;
}

MedicKit::MedicKit(const Point& center) : Item(center) {
  health_recovered = ConfigLoader::medic_kit_health_recovered;
}

void MedicKit::use(Player& user) { user.add_health(health_recovered); }

bool MedicKit::can_be_used_by(const Player& whom) { return !whom.is_full_health(); }

Item* MedicKit::copy() { return new MedicKit(position.get_origin(), id); }
