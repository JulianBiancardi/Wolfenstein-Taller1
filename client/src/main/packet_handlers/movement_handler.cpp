#include "movement_handler.h"

#include "../../../../common/src/main/packets/packing.h"

MovementHandler::MovementHandler() {}

MovementHandler::~MovementHandler() {}

void MovementHandler::handle(Packet& packet, Map& map) {
  unsigned char type;
  unsigned int player_id;
  unsigned char match_id;
  unsigned char dir;
  unpack(packet.get_data(), "CICC", &type, &player_id, &match_id, &dir);
  map.move_player(player_id, dir);
}