#include "rocket_launcher.h"

// const int RocketLauncher::bullet_required =
// ConfigLoader::get_init_configs().rocket_launcher_bullet_required; const int
// RocketLauncher::base_precision =
// ConfigLoader::get_init_configs().rocket_launcher_base_precision;

RocketLauncher::RocketLauncher() {}

void RocketLauncher::shoot(Player& player_shooting, int& current_bullets,
                           Map& map) {
  // Randomizo el daño con random
  std::random_device rd;     // Creo la semilla (toma info aleatoria del SO)
  std::mt19937_64 mt(rd());  // Genero un valor pseudo-aleatorio de 64 bits.
  std::uniform_int_distribution<int> damage_dist(1, 10);

  return;
  // shooter.receive_damage(damage_dist(mt));
}
