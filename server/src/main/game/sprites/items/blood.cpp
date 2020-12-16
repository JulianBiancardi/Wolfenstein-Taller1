#include "blood.h"

Blood::Blood(Point center) : Items(center) {
  health_recovered = 1;
  less_than = 11;
}

void Blood::use(Player &user) {
  user.add_health(health_recovered);
}

bool Blood::can_be_used_by(Player &whom) {
  return whom.get_health() < less_than;
}

void Blood::remove() {

}
