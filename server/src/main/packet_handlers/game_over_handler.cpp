#include "game_over_handler.h"

#include "../../../../common/src/main/packets/packing.h"

GameOverHandler::GameOverHandler() {}

GameOverHandler::~GameOverHandler() {}

void GameOverHandler::handle(Packet& packet, ClientManager& client_manager,
                             MatchManager& match_manager) {
  unsigned char type;
  unsigned int read_match_id;
  unpack(packet.get_data(), "CI", &type, &read_match_id);

  auto match_id = (unsigned char) read_match_id;

  Match& match = match_manager.get_match(match_id);

  const std::unordered_set<unsigned int>& clients = match.get_players_ids();
  client_manager.send_to_all(clients, packet);

  match_manager.delete_match(match_id);
}
