#include "machine_gun_item.h"

#include "../../../../../../common/src/main/config_loader.h"
#include "../../../../../../common/src/main/ids/gun_ids.h"
#include "../../../../../../common/src/main/ids/map_ids.h"

MachineGunItem::MachineGunItem(const Ray& position, unsigned int resource_id,
                               unsigned int id)
    : Item(position, resource_id, id) {}

MachineGunItem::~MachineGunItem() {}

void MachineGunItem::use_on(Player& player) { player.add_gun(MACHINE_GUN_ID); }