#include "chain_cannon.h"

// const int ChainCannon::bullet_required =
// ConfigLoader::chain_cannon_bullet_required; const int
// ChainCannon::base_precision = ConfigLoader::chain_cannon_base_precision;

ChainCannon::ChainCannon() : Gun(0, 0) {}

Hit ChainCannon::shoot(Object& player, int& current_bullets, BaseMap& map,
                       const std::vector<std::shared_ptr<Object>>& objects) {}

Hit ChainCannon::trigger(Object& player, int& current_bullets, BaseMap& map,
                         const std::vector<std::shared_ptr<Object>>& objects) {}

void ChainCannon::untrigger() {}