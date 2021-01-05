#include "machine_gun.h"
#include "../../guns/machine_gun.h"

MachineGun::MachineGun(Point center, int id) : Items(center, id) {

}

void MachineGun::use(Player &user) {
  //user.add_gun(gun);
}

Items *MachineGun::copy() {
  return new MachineGun(center, id);
}

bool MachineGun::can_be_used_by(Player &whom) {
  //return !whom.has_gun(gun);
  return false;
}

void MachineGun::remove() {

}
