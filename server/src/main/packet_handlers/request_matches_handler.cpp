
#include "request_matches_handler.h"

#include "../../../../common/src/main/packets/packing.h"
#include "../game/match.h"

#define MAP_NAME_MAX_SIZE 64

RequestMatchesHandler::RequestMatchesHandler() {}

RequestMatchesHandler::~RequestMatchesHandler() {}

void RequestMatchesHandler::handle(Packet& packet,
                                   ClientManager& client_manager,
                                   MatchManager& match_manager) {
  unsigned char type;
  unsigned int player_id;
  unpack(packet.get_data(), "CI", &type, &player_id);

  const std::unordered_map<unsigned char, Match>& matches =
      match_manager.get_matches();

  unsigned char matches_amount = matches.size();
  unsigned char buf[MATCH_AMOUNT_SIZE];
  size_t size = pack(buf, "CIC", MATCH_AMOUNT, player_id, matches_amount);
  Packet packet(size, buf);

  std::unordered_map<unsigned char, Match>::const_iterator iter;
  for (iter = matches.begin(); iter != matches.end(); iter++) {
    const Match& match = (*iter).second;

    unsigned char type = MATCH_DATA;
    unsigned int client_id = player_id;
    unsigned char match_id = match.get_id();
    char* map_name = match.get_map_name();
    unsigned char players_joined = match.get_players().size();
    unsigned char players_total = match.get_capacity();
    unsigned char status = match.has_started();

    unsigned char data[100];
    size = pack(data, "CICsCCC", type, client_id, match_id, map_name,
                players_joined, players_total, status);
    Packet packet(size, data);
    client_manager.send_to(client_id, packet);
  }
}