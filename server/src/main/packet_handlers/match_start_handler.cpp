#include "match_start_handler.h"

#include "../../../../common/src/main/packets/packing.h"
#include "../managers/match.h"

MatchStartHandler::MatchStartHandler() {}

MatchStartHandler::~MatchStartHandler() {}

void MatchStartHandler::handle(Packet& packet, ClientManager& client_manager,
                               MatchManager& match_manager) {
  unsigned char type;
  unsigned int player_id;
  unsigned char match_id;
  unpack(packet.get_data(), "CIC", &type, &player_id, &match_id);

  printf("A\n");
  Match& match = match_manager.get_match(match_id);
  printf("B\n");

  if (match.start(player_id, client_manager.get_reception_queue())) {
    printf("C\n");
    const std::unordered_set<unsigned int>& client_ids =
        match.get_players_ids();
    printf("D\n");
    client_manager.send_to_all(client_ids, packet);
    printf("E\n");
  }
}
