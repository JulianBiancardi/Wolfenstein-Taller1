#include "bullets.h"

#include "../../../../../../common/src/main/config_loader.h"
#include "../../../../../../common/src/main/ids/map_ids.h"

Bullets::Bullets(const Ray& position, unsigned int resource_id, unsigned int id)
    : Item(position, resource_id, id) {}

Bullets::~Bullets() {}

void Bullets::use_on(Player& player) {
  player.add_bullets(CL::bullets_amount);
  player.use_previous_gun_if_has_to();
}
