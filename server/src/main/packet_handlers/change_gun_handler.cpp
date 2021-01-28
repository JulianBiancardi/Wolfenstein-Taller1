#include "change_gun_handler.h"

#include <vector>

#include "../../../../common/src/main/packets/packing.h"
#include "../game/match.h"

ChangeGunHandler::ChangeGunHandler() {}

ChangeGunHandler::~ChangeGunHandler() {}

void ChangeGunHandler::handle(Packet& packet, ClientManager& client_manager,
                              MatchManager& match_manager) {
  unsigned char type;
  unsigned char match_id;
  unsigned char player_id;
  unsigned char gun_id;
  unpack(packet.get_data(), "CCCC", &type, &match_id, &player_id, &gun_id);

  Match& match = match_manager.get_match(match_id);

  if (match.change_gun(player_id, gun_id)) {
    const std::unordered_set<unsigned int>& client_ids =
        match.get_players_ids();
    client_manager.send_to_all(client_ids, packet);
  }
}
