#include "shot_handler.h"

#include "../../../../../common/src/main/ids/gun_ids.h"
#include "../../../../../common/src/main/packets/packing.h"

ShotHandler::ShotHandler() {}

ShotHandler::~ShotHandler() {}

bool ShotHandler::handle(Packet& packet, Map& map, GameSound& sound) {
  unsigned char type;
  unsigned int player_id;
  unsigned char match_id;
  unsigned char objective_id;
  unsigned char damage;
  unsigned char gun_id;
  unpack(packet.get_data(), "CICCCC", &type, &player_id, &match_id,
         &objective_id, &damage, &gun_id);

  if (gun_id == KNIFE_ID) {
    sound.play_knife(map.get_player(player_id).get_position(), damage,
                     objective_id);
  } else {
    sound.play_shoot(map.get_player(player_id).get_position(), gun_id);
  }

  map.use_bullets(player_id, gun_id);

  if (!map.get_player(player_id).has_bullets_to_shoot_gun()) {
    map.make_player_remember_gun(player_id);
    map.change_gun(player_id, KNIFE_ID);
  }

  if (objective_id != 0) {
    map.shoot_player(objective_id, damage, player_id);
  }

  return true;
}
