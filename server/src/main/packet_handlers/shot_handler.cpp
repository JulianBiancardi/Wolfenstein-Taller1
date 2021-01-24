#include "shot_handler.h"

#include "../../../../common/src/main/packets/packing.h"

ShotHandler::ShotHandler() {}

ShotHandler::~ShotHandler() {}

void ShotHandler::handle(Packet& packet, ClientManager& client_manager,
                         MatchManager& match_manager) {
  unsigned char type;
  unsigned char match_id;
  unsigned char player_id;
  unsigned char objective_id;
  unsigned char damage;
  unpack(packet.get_data(), "CCCCC", &type, &match_id, &player_id,
         &objective_id, &damage);

  Match& match = match_manager.get_match(match_id);
  match.shoot_gun(player_id, objective_id, damage);
  // TODO Let everyone know so they reproduce the sound or change his gun if he
  // ran out of bullets #EVENT
  if (match.is_dead(objective_id)) {
    // TODO Drop items #EVENT
    if (match.has_lives(objective_id)) {
      // TODO Respawn #EVENT
    } else {
      // TODO Check for winning condition #EVENT
    }
  } else {
    // TODO Grab health items if over one
  }
}
