#include "blood.h"

Blood::Blood(Point center, int id) : Items(center, id) {
  health_recovered = 1;
  less_than = 11;
}

void Blood::use(Player &user) {
  user.add_health(health_recovered);
}

Items *Blood::copy() {
  return new Blood(center, id);
}

bool Blood::can_be_used_by(Player &whom) {
  return whom.get_health() < less_than;
}

void Blood::remove() {

}
