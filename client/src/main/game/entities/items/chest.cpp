#include "chest.h"

#include "../../../../../../common/src/main/config_loader.h"
#include "../../../../../../common/src/main/ids/map_ids.h"

Chest::Chest(const Ray& position, unsigned int resource_id, unsigned int id)
    : Item(position, resource_id, id) {}

Chest::~Chest() {}

void Chest::use_on(Player& player) { player.add_points(CL::chest_points); }
