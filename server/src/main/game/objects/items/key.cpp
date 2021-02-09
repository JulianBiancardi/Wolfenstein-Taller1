#include "key.h"

Key::Key(const Point& center, int id) : Item(center, id) {}

Key::Key(const Point& center) : Item(center) {}

void Key::use(Player& user) { user.add_key(); }

bool Key::can_be_used_by(const Player& whom) { return true; }

Item* Key::copy() { return new Key(position.get_origin(), id); }
