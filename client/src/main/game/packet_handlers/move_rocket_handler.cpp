#include "move_rocket_handler.h"

#include "../../../../common/src/main/packets/packing.h"

MoveRocketHandler::MoveRocketHandler() = default;

MoveRocketHandler::~MoveRocketHandler() = default;

void MoveRocketHandler::handle(Packet& packet, Map& map, GameSound& sound) {
  unsigned char type;
  unsigned int rocket_id;
  unsigned char match_id;
  unsigned int player_id;
  unpack(packet.get_data(), "CICI", &type, &rocket_id, &match_id, &player_id);

  map.move_rocket(rocket_id);
  // TODO Play sound
}
