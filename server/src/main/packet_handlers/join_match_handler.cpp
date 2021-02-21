#include "join_match_handler.h"

#include "../../../../common/src/main/ids/gun_ids.h"
#include "../../../../common/src/main/packets/packing.h"
#include "../../../../common/src/main/utils/point.h"
#include "../managers/match.h"
#include "assistants/spawn_player.h"

JoinMatchHandler::JoinMatchHandler() {}

JoinMatchHandler::~JoinMatchHandler() {}

void JoinMatchHandler::handle(Packet& packet, ClientManager& client_manager,
                              MatchManager& match_manager) {
  unsigned char type;
  unsigned int player_id;
  unsigned char player_gun;
  unsigned char match_id;
  unpack(packet.get_data(), "CICC", &type, &player_id, &player_gun, &match_id);

  Match& match = match_manager.get_match(match_id);

  if (player_gun == KNIFE_ID) {
    client_manager.send_to(player_id, packet);
    notify_spawn(player_id, player_gun, match, client_manager);
    notify_all_spawns(player_id, player_gun, match, client_manager);
  }else if (match.add_player(player_id)) {
    client_manager.send_to(player_id, packet);
    notify_spawn(player_id, player_gun, match, client_manager);
    notify_all_spawns(player_id, player_gun, match, client_manager);
  } else {
    pack(packet.get_data(), "CICC", type, player_id, player_gun, 0);
    client_manager.send_to(player_id, packet);
  }
}

void JoinMatchHandler::notify_spawn(unsigned int player_id,
                                    unsigned char player_gun, Match& match,
                                    ClientManager& client_manager) {
  SpawnPlayerAssistant assistant;
  Packet spawn_player_packet = assistant.build_packet(player_id,
                                                      player_gun, match);
  const std::unordered_set<unsigned int>& client_ids = match.get_players_ids();
  client_manager.send_to_all(client_ids, spawn_player_packet);
}

void JoinMatchHandler::notify_all_spawns(unsigned int player_id,
                                         unsigned char player_gun,
                                         Match& match,
                                         ClientManager& client_manager){

const std::unordered_map<unsigned int, Player>& players = match.get_players();
  std::unordered_map<unsigned int, Player>::const_iterator iter;
  for (iter = players.begin(); iter != players.end(); iter++) {
    const unsigned int id = iter->first;
    if (id == player_id) {
      continue;
    }

    SpawnPlayerAssistant assistant;
Packet spawn_player_packet = assistant.build_packet(id, player_gun, match);
    client_manager.send_to(player_id, spawn_player_packet);
  }
}