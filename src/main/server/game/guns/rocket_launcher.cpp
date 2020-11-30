#include "rocket_launcher.h"

RocketLauncher::RocketLauncher() {

}

void RocketLauncher::shoot(Player &shooter) {
    Gun::shoot(shooter);
}
