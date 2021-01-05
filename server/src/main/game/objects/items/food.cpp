#include "food.h"

Food::Food(Point center, int id) : Item(center, id) { health_recovered = 10; }

void Food::use(Player& user) { user.add_health(health_recovered); }

Item* Food::copy() { return new Food(position.get_origin(), id); }

bool Food::can_be_used_by(Player& whom) { return true; }

void Food::remove() {}
