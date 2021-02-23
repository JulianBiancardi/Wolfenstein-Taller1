#include "exit_match_handler.h"

ExitMatchHandler::ExitMatchHandler() = default;

ExitMatchHandler::~ExitMatchHandler() = default;

void ExitMatchHandler::handle(Packet& packet, ClientManager& client_manager,
                              MatchManager& match_manager) {
  unsigned char type;
  unsigned int player_id;
  unsigned char match_id;
  unpack(packet.get_data(), "CIC", &type, &player_id, &match_id);

  Match& match = match_manager.get_match(match_id);

  match.delete_player(player_id);
}
