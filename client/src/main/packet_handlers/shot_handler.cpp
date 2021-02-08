#include "shot_handler.h"

#include "../../../../common/src/main/packets/packing.h"

ShotHandler::ShotHandler() {}

ShotHandler::~ShotHandler() {}

void ShotHandler::handle(Packet &packet, Map &map, GameSound &sound) {
  unsigned char type;
  unsigned int player_id;
  unsigned char match_id;
  unsigned char objective_id;
  unsigned char damage;
  unsigned char bullets_used;
  unpack(packet.get_data(), "CICCCC", &type, &player_id, &match_id,
         &objective_id, &damage, &bullets_used);

  // TODO Reproduce gun sound
  printf("Pum! *Hace ruido el arma* \n");
  map.use_bullets(player_id, bullets_used);
  printf("Bullets: %d\n", map.get_player(player_id).get_bullets());
  if (objective_id != 0) {
    printf("*Horror Screams* AHH! You hit me!\n");
    map.shoot_player(objective_id, damage);
  } else {
    printf("You missed you fucking idiot. Git gud!\n");
  }
}
