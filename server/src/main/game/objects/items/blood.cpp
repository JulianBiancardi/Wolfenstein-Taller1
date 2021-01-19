#include "blood.h"

Blood::Blood(Point center)
    : Item(center),
      health_recovered(CL::blood_health_recovered),
      less_than(CL::blood_health_recovered_if_less_than) {}

Blood::Blood(Point center, int id)
    : Item(center, id),
      health_recovered(CL::blood_health_recovered),
      less_than(CL::blood_health_recovered_if_less_than) {}

void Blood::use(Player& user) { user.add_health(health_recovered); }

Item* Blood::copy() { return new Blood(position.get_origin(), id); }

bool Blood::can_be_used_by(Player& whom) {
  return whom.get_health() < less_than;
}
