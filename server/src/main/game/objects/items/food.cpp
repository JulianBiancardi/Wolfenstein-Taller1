#include "food.h"

Food::Food(Point center)
    : Item(center),
      health_recovered(CL::food_health_recovered) {}

Food::Food(Point center, int id)
    : Item(center, id),
      health_recovered(CL::food_health_recovered) {}

void Food::use(Player& user) { user.add_health(health_recovered); }

Item* Food::copy() { return new Food(position.get_origin(), id); }

bool Food::can_be_used_by(Player& whom) { return !whom.is_full_health(); }
