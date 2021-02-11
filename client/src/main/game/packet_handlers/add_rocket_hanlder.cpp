#include "add_rocket_hanlder.h"

#include "../../../../common/src/main/packets/packing.h"

AddRocketHandler::AddRocketHandler() = default;

AddRocketHandler::~AddRocketHandler() = default;

void AddRocketHandler::handle(Packet& packet, Map& map, GameSound& sound) {
  unsigned char type;
  unsigned int player_id;
  unsigned int rocket_id;
  unpack(packet.get_data(), "CII", &type, &player_id, &rocket_id);
  map.shoot_rocket(player_id, rocket_id);
  // TODO Play sound
}
