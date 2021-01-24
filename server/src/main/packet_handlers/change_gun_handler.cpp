#include "change_gun_handler.h"

/*
void ChangeGunHandler::handle(Match& match, CollisionChecker& checker) {
  who.change_gun(gun);

  match.enqueue_result_for_all_others(
      build_change_gun_packet(who.get_id(), gun), who.get_id());
}*/

#include "../../../../common/src/main/packets/packing.h"

ChangeGunHandler::ChangeGunHandler() {}

ChangeGunHandler::~ChangeGunHandler() {}

void ChangeGunHandler::handle(Packet& packet, ClientManager& client_manager,
                              MatchManager& match_manager) {
  unsigned char type;
  unsigned char match_id;
  unsigned char player_id;
  unsigned char gun_id;
  unpack(packet.get_data(), "CCCC", &type, &match_id, &player_id, &gun_id);

  match_manager.change_gun(match_id, player_id, gun_id);
}
