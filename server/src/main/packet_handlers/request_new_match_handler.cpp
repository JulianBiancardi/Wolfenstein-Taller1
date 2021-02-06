#include "request_new_match_handler.h"

#include <string>

#include "../../../../common/src/main/packets/packing.h"
#include "../managers/match.h"

RequestNewMatchHandler::RequestNewMatchHandler() {}

RequestNewMatchHandler::~RequestNewMatchHandler() {}

void RequestNewMatchHandler::handle(Packet& packet,
                                    ClientManager& client_manager,
                                    MatchManager& match_manager) {
  unsigned char type;
  unsigned int player_id;
  char map_name[MAP_NAME_MAX_SIZE];
  unpack(packet.get_data(), "CIs", &type, &player_id, map_name);

  // TODO Check if map is in server
  if (true) {
    std::string file_name(map_name);
    unsigned char match_id = match_manager.create_match(player_id, file_name);

    if (match_id != 0) {
      Match& match = match_manager.get_match(match_id);
      match.add_player(player_id);
    }

    unsigned char buf[JOIN_MATCH_SIZE];
    size_t size = pack(buf, "CIC", JOIN_MATCH, player_id, match_id);
    Packet join_match_packet(size, buf);
    client_manager.send_to(player_id, join_match_packet);
    notify_spawn(player_id, match_id, client_manager, match_manager);
  }
}

void RequestNewMatchHandler::notify_spawn(unsigned int player_id,
                                          unsigned char match_id,
                                          ClientManager& client_manager,
                                          MatchManager& match_manager) {
  Match& match = match_manager.get_match(match_id);
  Point pos = match.get_players().at(player_id).get_position();

  unsigned char data[SPAWN_PLAYER_SIZE];
  size_t size = pack(data, "CICC", SPAWN_PLAYER, player_id, (int)pos.getX(),
                     (int)pos.getY());
  Packet spawn_player_packet(size, data);
  const std::unordered_set<unsigned int>& client_ids = match.get_players_ids();
  client_manager.send_to_all(client_ids, spawn_player_packet);
}
