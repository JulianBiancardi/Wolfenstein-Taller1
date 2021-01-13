#include "bullets.h"

Bullets::Bullets(Point center, int id) : Item(center, id),
                                         amount(5) {} //TODO Use config loader

void Bullets::use(Player& user) { user.add_bullets(amount); }

Item* Bullets::copy() { return new Bullets(position.get_origin(), id); }

bool Bullets::can_be_used_by(Player& whom) {
  return true;  // TODO Change
}

void Bullets::remove() {}
