#include "blood.h"

Blood::Blood(const Point& center, unsigned int id)
    : Item(center, id),
      health_recovered(CL::blood_health_recovered),
      less_than(CL::blood_health_recovered_if_less_than) {}

void Blood::use(Player& user) { user.add_health(health_recovered); }

bool Blood::can_be_used_by(const Player& whom) {
  return whom.get_health() < less_than;
}
