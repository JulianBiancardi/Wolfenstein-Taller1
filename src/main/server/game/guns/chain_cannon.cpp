#include "chain_cannon.h"

const int ChainCannon::bullet_required = ConfigLoader::get_init_configs().chain_cannon_bullet_required;
const int ChainCannon::base_precision = ConfigLoader::get_init_configs().chain_cannon_base_precision;

ChainCannon::ChainCannon() {
}

void ChainCannon::shoot(Player &shooter) {
    //Randomizo el daño con random
    std::random_device rd; //Creo la semilla (toma info aleatoria del SO)
    std::mt19937_64 mt(rd()); //Genero un valor pseudo-aleatorio de 64 bits.
    std::uniform_int_distribution<int> damage_dist(1, 10);

    shooter.receive_damage(damage_dist(mt));

}
