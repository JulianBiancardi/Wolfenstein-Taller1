#include "food.h"

#include <utility>

#include "../../../../../../common/src/main/ids/map_ids.h"

Food::Food(const Point& center, int id)
    : Item(center, id), health_recovered(CL::food_health_recovered) {}

Food::Food(const Point& center)
    : Item(center), health_recovered(CL::food_health_recovered) {}

void Food::use(Player& user) { user.add_health(health_recovered); }

bool Food::can_be_used_by(const Player& whom) { return !whom.is_full_health(); }

Item* Food::copy() { return new Food(position.get_origin(), id); }

Packet Food::get_add_item_packet() {
  unsigned char data[ADD_ITEM_SIZE];
  size_t size =
      pack(data, "CICCC", ADD_ITEM, id, FOOD, (int)position.get_origin().getX(),
           (int)position.get_origin().getY());
  return std::move(Packet(size, data));
}
