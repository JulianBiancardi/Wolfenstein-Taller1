#include "medic_kit.h"

MedicKit::MedicKit(Point center) : Item(center) {
  health_recovered = ConfigLoader::medic_kit_health_recovered;
}

MedicKit::MedicKit(Point center, int id) : Item(center, id) {
  health_recovered = ConfigLoader::medic_kit_health_recovered;
}

void MedicKit::use(Player& user) { user.add_health(health_recovered); }

Item* MedicKit::copy() { return new MedicKit(position.get_origin(), id); }

bool MedicKit::can_be_used_by(Player& whom) { return !whom.is_full_health(); }

void MedicKit::remove() {}
