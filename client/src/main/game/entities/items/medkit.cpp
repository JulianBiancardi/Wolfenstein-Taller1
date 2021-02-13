#include "medkit.h"

#include "../../../../../../common/src/main/ids/map_ids.h"

Medkit::Medkit(Ray& position, unsigned int id)
    : IdentifiableObject(position, id) {}

Medkit::~Medkit() {}

Image* Medkit::get_image(ResourceManager& resource_manager) {
  return resource_manager.get_image(MEDKIT);
}

void use_on(Player& player) {
  player.set_health(std::min(
      CL::player_health, player.get_health() + CL::medic_kit_health_recovered));
}