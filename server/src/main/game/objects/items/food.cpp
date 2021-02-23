#include "food.h"

Food::Food(const Point& center, unsigned int id)
    : Item(center, id), health_recovered(CL::food_health_recovered) {}

void Food::use(Player& user) { user.add_health(health_recovered); }

bool Food::can_be_used_by(const Player& whom) { return !whom.is_full_health(); }
