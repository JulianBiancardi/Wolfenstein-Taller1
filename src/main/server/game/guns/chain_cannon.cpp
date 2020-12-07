#include "chain_cannon.h"

//const int ChainCannon::bullet_required = ConfigLoader::chain_cannon_bullet_required;
//const int ChainCannon::base_precision = ConfigLoader::chain_cannon_base_precision;

ChainCannon::ChainCannon() {
}

int ChainCannon::shoot(int &available_bullets) {
  if (available_bullets < ConfigLoader::chain_cannon_bullet_required)
    return 0;
  available_bullets -= ConfigLoader::chain_cannon_bullet_required;

  //Randomizo el daño
  std::random_device rd; //Creo la semilla (toma info aleatoria del SO)
  std::mt19937_64 mt(rd()); //Genero un valor pseudo-aleatorio de 64 bits.
  std::uniform_int_distribution<int> damage_dist(1, 10);

  return damage_dist(mt);
}
