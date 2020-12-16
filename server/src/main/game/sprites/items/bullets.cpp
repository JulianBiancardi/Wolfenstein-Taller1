#include "bullets.h"

Bullets::Bullets(Point center) : Items(center) {
  amount = 5;
}

void Bullets::use(Player &user) {
  user.add_bullets(amount);
}

bool Bullets::can_be_used_by(Player &whom) {
  return true;
}

void Bullets::remove() {

}
