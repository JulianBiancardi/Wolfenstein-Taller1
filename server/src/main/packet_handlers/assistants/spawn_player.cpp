#include "spawn_player.h"
#include <utility>

SpawnPlayerAssistant::SpawnPlayerAssistant() {}

SpawnPlayerAssistant::~SpawnPlayerAssistant() {}

Packet SpawnPlayerAssistant::build_packet(unsigned int player_id,
                                          unsigned char player_gun,
                                          Match& match) {
  Point pos = match.get_players().at(player_id).get_position();

  unsigned char data[SPAWN_PLAYER_SIZE];
  size_t size = pack(data, "CICCC", SPAWN_PLAYER, player_id, player_gun,
                     (int)pos.getX(), (int)pos.getY());

  Packet spawn_player_packet(size, data);
  return std::move(Packet(size, data));
}