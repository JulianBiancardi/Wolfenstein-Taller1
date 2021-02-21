#include "add_rocket_handler.h"

#include "../../../../../common/src/main/packets/packing.h"

AddRocketHandler::AddRocketHandler() = default;

AddRocketHandler::~AddRocketHandler() = default;

bool AddRocketHandler::handle(Packet& packet, Map& map, GameSound& sound) {
  unsigned char type;
  unsigned int player_id;
  unpack(packet.get_data(), "CI", &type, &player_id);
  map.shoot_rocket(player_id);
  // TODO Play sound

  return true;
}
