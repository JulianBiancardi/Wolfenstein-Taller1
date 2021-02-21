#include "movement_handler.h"

#include "../../../../../common/src/main/packets/packing.h"

MovementHandler::MovementHandler() {}

MovementHandler::~MovementHandler() {}

bool MovementHandler::handle(Packet& packet, Map& map, GameSound& sound) {
  unsigned char type;
  unsigned int player_id;
  unsigned char match_id;
  unsigned char dir;
  unpack(packet.get_data(), "CICC", &type, &player_id, &match_id, &dir);
  map.move_player(player_id, dir);
  sound.set_point(map.get_player(player_id).get_position());

  return true;
}