#include "machine_gun.h"

// const int MachineGun::bullet_required =
// ConfigLoader::get_init_configs().machine_gun_bullet_required; const int
// MachineGun::base_precision =
// ConfigLoader::get_init_configs().machine_gun_base_precision;

MachineGun::MachineGun() : Gun(1, 50) {}

Hit MachineGun::shoot(Object& player, int& current_bullets, Map& map) {
  // Randomizo el daño con random
  std::random_device rd;     // Creo la semilla (toma info aleatoria del SO)
  std::mt19937_64 mt(rd());  // Genero un valor pseudo-aleatorio de 64 bits.
  std::uniform_int_distribution<int> damage_dist(1, 10);

  return Hit(-1, 0);
  // shooter.receive_damage(damage_dist(mt));
}
