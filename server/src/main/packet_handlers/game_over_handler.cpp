#include "game_over_handler.h"

#include "../../../../common/src/main/packets/packing.h"
#include "../managers/match.h"

GameOverHandler::GameOverHandler() {}

GameOverHandler::~GameOverHandler() {}

void GameOverHandler::handle(Packet& packet, ClientManager& client_manager,
                             MatchManager& match_manager) {
  unsigned char type;
  unsigned char match_id;
  unpack(packet.get_data(), "CC", &type, &match_id);

  Match& match = match_manager.get_match(match_id);

  const std::unordered_set<unsigned int>& client_ids = match.get_players_ids();
  client_manager.send_to_all(client_ids, packet);

  match.end();
}
