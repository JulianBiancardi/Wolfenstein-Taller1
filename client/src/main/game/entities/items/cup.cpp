#include "cup.h"

#include "../../../../../../common/src/main/config_loader.h"
#include "../../../../../../common/src/main/ids/map_ids.h"

Cup::Cup(const Ray& position, unsigned int resource_id, unsigned int id)
    : Item(position, resource_id, id) {}

Cup::~Cup() {}

void Cup::use_on(Player& player) { player.add_points(CL::cup_points); }
