#include "knife.h"

// const int Knife::range = ConfigLoader::get_init_configs().knife_range;

Knife::Knife() : Gun(0, 2) {}

Hit Knife::shoot(Object& player, int& current_bullets, BaseMap& map,
                 const std::vector<Object*>& objects) {}
