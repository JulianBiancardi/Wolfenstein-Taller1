#include "rocket_move_handler.h"

#include "../../../../common/src/main/packets/packing.h"

RocketMoveHandler::RocketMoveHandler() {}

RocketMoveHandler::~RocketMoveHandler() {}

void RocketMoveHandler::handle(Packet& packet, ClientManager& client_manager,
                               MatchManager& match_manager) {
  unsigned char type;
  unsigned char rocket_id;
  unsigned char match_id;
  unsigned int player_id;
  unpack(packet.get_data(), "CICI", &type, &rocket_id, &match_id, &player_id);

  Match& match = match_manager.get_match(match_id);

  const std::unordered_set<unsigned int>& clients = match.get_players_ids();

  client_manager.send_to_all(clients, packet);

  if (!match.move_rocket(rocket_id)) {
    std::unordered_map<unsigned int, unsigned char> players_exploded =
        match.explode_rocket(rocket_id, player_id);

    unsigned char data[ROCKET_EXPLODE_SIZE];
    size_t size = pack(data, "CI", ROCKET_EXPLODE, &rocket_id);

    for (auto player_exploded : players_exploded) {
      size += pack(data, "IC", &player_exploded.first, &player_exploded.second);
    }

    Packet explosion_packet(size, data);

    client_manager.send_to_all(clients, explosion_packet);
  }
}
