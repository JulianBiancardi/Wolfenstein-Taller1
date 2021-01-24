#include "change_gun_handler.h"

/*
void ChangeGunHandler::handle(Match& match, CollisionChecker& checker) {
  who.change_gun(gun);

  match.enqueue_result_for_all_others(
      build_change_gun_packet(who.get_id(), gun), who.get_id());
}*/

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
    std::vector<unsigned char>& client_ids = match.get_players_ids();
    client_manager.send_to_all(client_ids, packet);
  }
}
