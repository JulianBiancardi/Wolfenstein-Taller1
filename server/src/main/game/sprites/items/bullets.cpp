#include "bullets.h"

Bullets::Bullets(Point center, int id) : Items(center, id) {
  amount = 5;
}

void Bullets::use(Player &user) {
  user.add_bullets(amount);
}

Items *Bullets::copy() {
  return new Bullets(center, id);
}

bool Bullets::can_be_used_by(Player &whom) {
  return true; // TODO Change
}

void Bullets::remove() {

}
