#include "explode_rocket_handler.h"

#include "../../../../../common/src/main/packets/packing.h"

ExplodeRocketHandler::ExplodeRocketHandler() = default;

ExplodeRocketHandler::~ExplodeRocketHandler() = default;

void ExplodeRocketHandler::handle(Packet& packet, Map& map, GameSound& sound) {
  unsigned char type;
  unsigned int rocket_id;
  unpack(packet.get_data(), "CI", &type, &rocket_id);

  unsigned int player_id;
  unsigned char damage;

  unsigned int players_exploded = (packet.get_size() - 3) / 3;
  for (unsigned int i = 0; i < players_exploded; i++) {
    unpack(packet.get_data() + i * 3 + 3, "IC", &player_id, &damage);
    map.shoot_player(player_id, damage, map.get_rocket_owner_id(rocket_id));
  }

  // TODO Play sound
}
