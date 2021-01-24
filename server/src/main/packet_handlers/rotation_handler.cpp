#include "rotation_handler.h"

#include "../../../../common/src/main/packets/packing.h"

RotationHandler::RotationHandler() {}

RotationHandler::~RotationHandler() {}

void RotationHandler::handle(Packet& packet, ClientManager& client_manager,
                             MatchManager& match_manager) {
  unsigned char type;
  unsigned char match_id;
  unsigned char player_id;
  unsigned char direction;
  unpack(packet.get_data(), "CCCC", &type, &match_id, &player_id, &direction);

  match_manager.rotate_player(match_id, player_id, direction);
}
