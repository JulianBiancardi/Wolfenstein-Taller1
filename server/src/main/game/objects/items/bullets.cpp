#include "bullets.h"

Bullets::Bullets(const Point& center, int amount, unsigned int id)
    : Item(center, id), amount(amount) {}

void Bullets::use(Player& user) {
  user.add_bullets(amount);
  user.use_previous_gun_if_has_to();
}

bool Bullets::can_be_used_by(const Player& whom) {
  return !whom.is_full_bullets();
}
