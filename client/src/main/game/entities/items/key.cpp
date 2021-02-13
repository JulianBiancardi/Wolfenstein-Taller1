#include "key.h"

#include "../../../../../../common/src/main/config_loader.h"
#include "../../../../../../common/src/main/ids/map_ids.h"

Key::Key(const Ray& position, unsigned int resource_id, unsigned int id)
    : Item(position, resource_id, id) {}

Key::~Key() {}

void Key::use_on(Player& player) { player.add_key(); }
