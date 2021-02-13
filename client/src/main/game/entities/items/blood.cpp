#include "blood.h"

#include "../../../../../../common/src/main/config_loader.h"
#include "../../../../../../common/src/main/ids/map_ids.h"

Blood::Blood(const Ray& position, unsigned int resource_id, unsigned int id)
    : Item(position, resource_id, id) {}

Blood::~Blood() {}

void Blood::use_on(Player& player) {
  player.add_health(CL::blood_health_recovered);
}
