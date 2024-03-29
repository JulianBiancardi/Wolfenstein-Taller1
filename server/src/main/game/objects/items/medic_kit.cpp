#include "medic_kit.h"

MedicKit::MedicKit(const Point& center, unsigned int id)
    : Item(center, id), health_recovered(CL::medic_kit_health_recovered) {}

void MedicKit::use(Player& user) { user.add_health(health_recovered); }

bool MedicKit::can_be_used_by(const Player& whom) {
  return !whom.is_full_health();
}
