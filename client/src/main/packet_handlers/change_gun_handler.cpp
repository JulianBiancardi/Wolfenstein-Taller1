#include "change_gun_handler.h"

#include "../../../../common/src/main/packets/packing.h"

ChangeGunHandler::ChangeGunHandler() {}

ChangeGunHandler::~ChangeGunHandler() {}

void ChangeGunHandler::handle(Packet &packet, Map &map, GameSound &sound) {
  unsigned char type;
  unsigned int player_id;
  unsigned char match_id;
  unsigned char gun_id;
  unpack(packet.get_data(), "CICC", &type, &player_id, &match_id, &gun_id);

  if (map.get_player(player_id).get_gun() != gun_id) {
    map.untrigger_gun(player_id);
    map.change_gun(player_id, gun_id);
    printf("*Ruido de Cambiar arma de Counter*\n");
  }
}