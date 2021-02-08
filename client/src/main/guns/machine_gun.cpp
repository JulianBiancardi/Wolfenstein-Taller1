#include "machine_gun.h"

// const int MachineGun::bullet_required =
// ConfigLoader::get_init_configs().machine_gun_bullet_required; const int
// MachineGun::base_precision =
// ConfigLoader::get_init_configs().machine_gun_base_precision;

MachineGun::MachineGun() : Gun(1, 50) {}

Hit MachineGun::shoot(Object& player, int& current_bullets, BaseMap& map,
                      const std::vector<std::shared_ptr<Object>>& objects) {}

Hit MachineGun::trigger(Object& player, int& current_bullets, BaseMap& map,
                        const std::vector<std::shared_ptr<Object>>& objects) {}

void MachineGun::untrigger() {}
