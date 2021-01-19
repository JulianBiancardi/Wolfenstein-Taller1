#include "bullets.h"

Bullets::Bullets(Point center)
    : Item(center), amount(CL::bullets_amount) {}

Bullets::Bullets(Point center, int id)
    : Item(center, id), amount(CL::bullets_amount) {}

void Bullets::use(Player& user) { user.add_bullets(amount); }

Item* Bullets::copy() { return new Bullets(position.get_origin(), id); }

bool Bullets::can_be_used_by(Player& whom) {
  return !whom.is_full_bullets();
}
