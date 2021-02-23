#include "add_rocket_handler.h"

#include "../../../../../common/src/main/ids/gun_ids.h"
#include "../../../../../common/src/main/packets/packing.h"

AddRocketHandler::AddRocketHandler() = default;

AddRocketHandler::~AddRocketHandler() = default;

bool AddRocketHandler::handle(Packet& packet, Map& map, GameSound& sound) {
  unsigned char type;
  unsigned int player_id;
  unpack(packet.get_data(), "CI", &type, &player_id);
  map.shoot_rocket(player_id);

  if (!map.get_player(player_id).has_bullets_to_shoot_gun()) {
    map.make_player_remember_gun(player_id);
    map.change_gun(player_id, KNIFE_ID);
  }

  return true;
}
