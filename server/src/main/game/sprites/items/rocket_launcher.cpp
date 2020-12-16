#include "rocket_launcher.h"
#include "../../guns/rocket_launcher.h"

RocketLauncher::RocketLauncher(Point center) : Items(center) {

}

void RocketLauncher::use(Player &user) {
  //user.add_gun(gun);
}

bool RocketLauncher::can_be_used_by(Player &whom) {
  //return !whom.has_gun(gun);
  return false;
}

void RocketLauncher::remove() {

}
