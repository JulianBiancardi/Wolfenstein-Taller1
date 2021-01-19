#include "bullets.h"

Bullets::Bullets(Point center, int amount)
    : Item(center), amount(amount) {}

Bullets::Bullets(Point center, int amount, int id)
    : Item(center, id), amount(amount) {}

void Bullets::use(Player& user) { user.add_bullets(amount); }

Item* Bullets::copy() { return new Bullets(position.get_origin(), amount, id); }

bool Bullets::can_be_used_by(Player& whom) {
  return !whom.is_full_bullets();
}
