#include "request_new_match_handler.h"

#include "../../../../common/src/main/packets/packing.h"
#include "../game/match.h"

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
    std::string map_name(map_name);
    unsigned char match_id = match_manager.create_match(map_name);

    if (match_id != 0) {
      Match& match = match_manager.get_match(match_id);
      match.add_player(player_id);
    }

    unsigned char buf[JOIN_MATCH_SIZE];
    size_t size = pack(buf, "CIC", JOIN_MATCH, player_id, match_id);
    Packet join_match_packet(size, buf);
    client_manager.send_to(player_id, join_match_packet);
  }
}