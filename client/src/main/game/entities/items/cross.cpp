#include "cross.h"

#include "../../../../../../common/src/main/config_loader.h"
#include "../../../../../../common/src/main/ids/map_ids.h"

Cross::Cross(const Ray& position, unsigned int resource_id, unsigned int id)
    : Item(position, resource_id, id) {}

Cross::~Cross() {}

void Cross::use_on(Player& player) { player.add_points(CL::cross_points); }
