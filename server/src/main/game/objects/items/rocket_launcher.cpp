#include "rocket_launcher.h"
#include "../../guns/rocket_launcher.h"

RocketLauncher::RocketLauncher(Point center, int id) : Items(center, id) {

}

void RocketLauncher::use(Player &user) {
  //user.add_gun(gun);
}

Items *RocketLauncher::copy() {
  return new RocketLauncher(center, id);
}

bool RocketLauncher::can_be_used_by(Player &whom) {
  //return !whom.has_gun(gun);
  return false;
}

void RocketLauncher::remove() {

}
