#include "move_handler.h"

#include <vector>

#include "../../../../common/src/main/packets/packing.h"
#include "../managers/match.h"

MoveHandler::MoveHandler() {}

MoveHandler::~MoveHandler() {}

void MoveHandler::handle(Packet& packet, ClientManager& client_manager,
                         MatchManager& match_manager) {
  unsigned char type;
  unsigned int player_id;
  unsigned char match_id;
  unsigned char dir;
  unpack(packet.get_data(), "CICC", &type, &player_id, &match_id, &dir);

  Match& match = match_manager.get_match(match_id);

  if (match.move_player(player_id, dir)) {
    const std::unordered_set<unsigned int>& clients = match.get_players_ids();
    client_manager.send_to_all(clients, packet);

    consequent_grab(player_id, match, client_manager);
  }
}