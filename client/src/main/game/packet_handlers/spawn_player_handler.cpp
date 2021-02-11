#include "spawn_player_handler.h"

#include "../../../../../common/src/main/packets/packing.h"

SpawnPlayerHandler::SpawnPlayerHandler() {}

SpawnPlayerHandler::~SpawnPlayerHandler() {}

void SpawnPlayerHandler::handle(Packet &packet, Map &map, GameSound &sound) {
  unsigned char type;
  unsigned int player_id;
  unsigned char x_pos;
  unsigned char y_pos;
  unpack(packet.get_data(), "CICC", &type, &player_id, &x_pos, &y_pos);

  map.add_player(player_id, Ray(x_pos + 0.5, y_pos + 0.5, 0));
}