#include "rotation_handler.h"

#include "../../../../../common/src/main/packets/packing.h"

RotationHandler::RotationHandler() {}

RotationHandler::~RotationHandler() {}

void RotationHandler::handle(Packet &packet, Map &map, GameSound &sound) {
  unsigned char type;
  unsigned int player_id;
  unsigned char match_id;
  unsigned char direction;
  unpack(packet.get_data(), "CICC", &type, &player_id, &match_id, &direction);

  map.rotate_player(player_id, direction);
}
