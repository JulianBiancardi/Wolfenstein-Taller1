#include "../../../../common/src/main/packets/packing.h"
#include "../managers/match.h"
#include "join_match_handler.h"

JoinMatchHandler::JoinMatchHandler() {}

JoinMatchHandler::~JoinMatchHandler() {}

void JoinMatchHandler::handle(Packet& packet, ClientManager& client_manager,
                              MatchManager& match_manager) {
  unsigned char type;
  unsigned int player_id;
  unsigned char match_id;
  unpack(packet.get_data(), "CIC", &type, &player_id, &match_id);

  Match& match = match_manager.get_match(match_id);

  if (match.start(player_id)) {
    const std::unordered_set<unsigned int>& client_ids =
        match.get_players_ids();
    client_manager.send_to_all(client_ids, packet);
  }
}
