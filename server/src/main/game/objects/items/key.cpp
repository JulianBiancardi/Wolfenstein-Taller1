#include "key.h"

Key::Key(Point center) : Item(center) {}

Key::Key(Point center, int id) : Item(center, id) {}

void Key::use(Player& user) {}

Item* Key::copy() { return new Key(position.get_origin(), id); }

bool Key::can_be_used_by(Player& whom) { return true; }

void Key::remove() {}
