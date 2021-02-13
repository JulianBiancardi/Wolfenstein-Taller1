#include "crown.h"

#include "../../../../../../common/src/main/config_loader.h"
#include "../../../../../../common/src/main/ids/map_ids.h"

Crown::Crown(const Ray& position, unsigned int resource_id, unsigned int id)
    : Item(position, resource_id, id) {}

Crown::~Crown() {}

void Crown::use_on(Player& player) { player.add_points(CL::crown_points); }
