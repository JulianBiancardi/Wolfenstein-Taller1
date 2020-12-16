#include "medic_kit.h"

MedicKit::MedicKit(Point center) : Items(center) {
  health_recovered = 20; // TODO Use config loader
}

void MedicKit::use(Player &user) {
  user.add_health(health_recovered);
}

bool MedicKit::can_be_used_by(Player &whom) {
  return true;
}

void MedicKit::remove() {

}
