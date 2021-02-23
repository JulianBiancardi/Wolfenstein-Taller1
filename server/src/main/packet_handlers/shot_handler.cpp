#include "shot_handler.h"

#include "../../../../common/src/main/packets/packing.h"
#include "../../../../common/src/main/ids/gun_ids.h"

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
    match.shoot_rocket(player_id);

    unsigned char data[ROCKET_ADD_SIZE];
    size_t size = pack(data, "CI", ROCKET_ADD, player_id);
    Packet rocket_packet(size, data);

    client_manager.send_to_all(clients, rocket_packet);
  } else {
    match.shoot_gun(player_id, objective_id, damage);

    client_manager.send_to_all(clients, packet);

    if (objective_id != 0) {
      if (!match.is_dead(objective_id)) {
        consequent_grab(objective_id, match, client_manager);
      } else if (match.has_one_player_alive()) {
        game_over(match, client_manager);
      }
    }
  }

  if (!match.get_players().at(player_id).has_bullets_to_shoot_gun()) {
    match.make_player_remember_gun(player_id);
    match.change_gun(player_id, KNIFE_ID);
  }

  consequent_grab(player_id, match, client_manager);
}
