#include "medic_kit.h"

MedicKit::MedicKit(Point center, int id) : Items(center, id) {
  health_recovered = 20; // TODO Use config loader
}

void MedicKit::use(Player &user) {
  user.add_health(health_recovered);
}

Items *MedicKit::copy() {
  return new MedicKit(center, id);
}

bool MedicKit::can_be_used_by(Player &whom) {
  return !whom.is_full_health();
}

void MedicKit::remove() {

}
