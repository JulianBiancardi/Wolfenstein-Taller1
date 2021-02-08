#include "shot_handler.h"

#include "../../../../common/src/main/packets/packing.h"
#include "../managers/match.h"

ShotHandler::ShotHandler() {}

ShotHandler::~ShotHandler() {}

void ShotHandler::handle(Packet& packet, ClientManager& client_manager,
                         MatchManager& match_manager) {
  unsigned char type;
  unsigned int player_id;
  unsigned char match_id;
  unsigned char objective_id;
  unsigned char damage;
  unpack(packet.get_data(), "CICCC", &type, &player_id, &match_id,
         &objective_id, &damage);

  Match& match = match_manager.get_match(match_id);

  const std::unordered_set<unsigned int>& clients = match.get_players_ids();
  client_manager.send_to_all(clients, packet);

  if (match.shoot_gun(player_id, objective_id, damage)) {
    if (!match.is_dead(objective_id)) {
      consequent_grab(objective_id, match, client_manager);
    } else if (match.should_end()) {
      game_over(match, client_manager);
    }
  }

  consequent_grab(player_id, match, client_manager);
}
