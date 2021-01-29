#include "end_of_connection_handler.h"

#include <vector>

#include "../../../../common/src/main/packets/packing.h"
#include "../managers/match.h"

EndOfConnectionHandler::EndOfConnectionHandler() {}

EndOfConnectionHandler::~EndOfConnectionHandler() {}

void EndOfConnectionHandler::handle(Packet& packet,
                                    ClientManager& client_manager,
                                    MatchManager& match_manager) {
  unsigned char type;
  unsigned int player_id;
  unpack(packet.get_data(), "CI", &type, &player_id);

  client_manager.end_connection(player_id);

  unsigned char match_id = match_manager.find_match_of_player(player_id);
  if (match_id != 0) {
    const std::unordered_set<unsigned int>& client_ids =
        match_manager.get_match(match_id).get_players_ids();
    client_manager.send_to_all(client_ids, packet);
  }
}
