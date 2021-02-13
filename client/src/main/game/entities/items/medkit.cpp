#include "medkit.h"

#include "../../../../../../common/src/main/config_loader.h"
#include "../../../../../../common/src/main/ids/map_ids.h"

Medkit::Medkit(const Ray& position, unsigned int resource_id, unsigned int id)
    : Item(position, resource_id, id) {}

Medkit::~Medkit() {}

void Medkit::use_on(Player& player) {
  player.add_health(CL::medic_kit_health_recovered);
}
