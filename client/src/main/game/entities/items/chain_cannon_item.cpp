#include "chain_cannon_item.h"

#include "../../../../../../common/src/main/config_loader.h"
#include "../../../../../../common/src/main/ids/gun_ids.h"
#include "../../../../../../common/src/main/ids/map_ids.h"

ChainCannonItem::ChainCannonItem(const Ray& position, unsigned int resource_id,
                                 unsigned int id)
    : Item(position, resource_id, id) {}

ChainCannonItem::~ChainCannonItem() {}

void ChainCannonItem::use_on(Player& player) {
  player.add_gun(CHAIN_CANNON_ID);
}
