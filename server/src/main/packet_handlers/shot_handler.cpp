#include "shot_handler.h"

#include "../../../../common/src/main/packets/packing.h"

ShotHandler::ShotHandler() {}

ShotHandler::~ShotHandler() {}

void ShotHandler::handle(Packet& packet, ClientManager& client_manager,
                         MatchManager& match_manager) {
  unsigned char type;
  unsigned int player_id;
  unsigned char match_id;
  unsigned char objective_id;
  unsigned char damage;
  unsigned char bullets_used;
  unpack(packet.get_data(), "CICCCC", &type, &player_id, &match_id,
         &objective_id, &damage, &bullets_used);

  Match& match = match_manager.get_match(match_id);

  const std::unordered_set<unsigned int>& clients = match.get_players_ids();

  if (match.is_using_rocket_launcher(player_id)) {
    unsigned int rocket_id = match.shoot_rocket(player_id);

    unsigned char data[ROCKET_ADD_SIZE];
    size_t size = pack(data, "CII", ROCKET_ADD, player_id, rocket_id);
    Packet rocket_packet(size, data);

    client_manager.send_to_all(clients, rocket_packet);
  } else {
    match.shoot_gun(player_id, objective_id, damage);

    client_manager.send_to_all(clients, packet);

    if (objective_id != 0) {
      if (!match.is_dead(objective_id)) {
        // FIXME Remove Consequent grab since it is not POO. Use function or new
        // handler.
        consequent_grab(objective_id, match, client_manager);
      } else if (match.should_end()) {  // TODO Consider a better name
        game_over(match, client_manager);
      }
    }
  }

  consequent_grab(player_id, match, client_manager);
}
