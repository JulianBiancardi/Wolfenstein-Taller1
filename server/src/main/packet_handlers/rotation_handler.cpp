#include "rotation_handler.h"

#include <vector>

#include "../../../../common/src/main/packets/packing.h"
#include "../game/match.h"

RotationHandler::RotationHandler() {}

RotationHandler::~RotationHandler() {}

void RotationHandler::handle(Packet& packet, ClientManager& client_manager,
                             MatchManager& match_manager) {
  unsigned char type;
  unsigned char match_id;
  unsigned char player_id;
  unsigned char direction;
  unpack(packet.get_data(), "CCCC", &type, &match_id, &player_id, &direction);

  Match& match = match_manager.get_match(match_id);
  if (match.rotate_player(player_id, direction)) {
    std::vector<unsigned char>& client_ids = match.get_players_ids();
    client_manager.send_to_all(client_ids, packet);
  }
}
