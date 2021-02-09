#include "bullets.h"

Bullets::Bullets(const Point& center, int amount, int id)
    : Item(center, id), amount(amount) {}

Bullets::Bullets(const Point& center, int amount)
    : Item(center), amount(amount) {}

void Bullets::use(Player& user) { user.add_bullets(amount); }

bool Bullets::can_be_used_by(const Player& whom) {
  return !whom.is_full_bullets();
}

Item* Bullets::copy() { return new Bullets(position.get_origin(), amount, id); }
