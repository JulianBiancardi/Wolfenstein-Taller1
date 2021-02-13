#include "food.h"

#include "../../../../../../common/src/main/config_loader.h"
#include "../../../../../../common/src/main/ids/map_ids.h"

Food::Food(const Ray& position, unsigned int resource_id, unsigned int id)
    : Item(position, resource_id, id) {}

Food::~Food() {}

void Food::use_on(Player& player) {
  player.add_health(CL::food_health_recovered);
}
