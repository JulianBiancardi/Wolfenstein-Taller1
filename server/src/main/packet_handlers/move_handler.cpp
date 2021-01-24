#include "move_handler.h"

#include "../../game/match.h"
#include "../event_building.h"

/*
void MoveHandler::handle(Match& match, CollisionChecker& checker) {
  Point where = who.next_position(direction);

  if (checker.can_move(where, who)) {
    who.set_position(where);
    match.enqueue_result_for_all(build_move_packet(who.get_id(), direction));
    consequence_grab_event(match, checker, who);
  } else {
    match.enqueue_result_for_all(build_move_packet(who.get_id(), INVALID));
  }
}*/

#include "../../../../common/src/main/packets/packing.h"

MoveHandler::MoveHandler() {}

MoveHandler::~MoveHandler() {}

void MoveHandler::handle(Packet& packet, ClientManager& client_manager,
                         MatchManager& match_manager) {
  unsigned char type;
  unsigned char match_id;
  unsigned char player_id;
  unsigned char dir;
  unpack(packet.get_data(), "CCCC", &type, &match_id, &player_id, &dir);

  match_manager.move_player(match_id, player_id, dir);
}