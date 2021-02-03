#include "change_gun_handler.h"

#include "../../../../common/src/main/packets/packing.h"

ChangeGunHandler::ChangeGunHandler() {}

ChangeGunHandler::~ChangeGunHandler() {}

void ChangeGunHandler::handle(Packet& packet, ClientManager& client_manager,
                              MatchManager& match_manager) {
  unsigned char type;
  unsigned int player_id;
  unsigned char match_id;
  unsigned char gun_id;
  unpack(packet.get_data(), "CICC", &type, &player_id, &match_id, &gun_id);

  Match& match = match_manager.get_match(match_id);

  if (match.change_gun(player_id, gun_id)) {
    const std::unordered_set<unsigned int>& clients = match.get_players_ids();
    client_manager.send_to_all(clients, packet);
  }
}
