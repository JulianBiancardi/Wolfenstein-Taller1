#include "key.h"

Key::Key(const Point& center, unsigned int id)
    : Item(center, id) {}

void Key::use(Player& user) { user.add_key(); }

bool Key::can_be_used_by(const Player& whom) { return true; }
