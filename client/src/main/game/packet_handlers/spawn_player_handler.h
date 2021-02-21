#ifndef SPAWN_PLAYER_HANDLER_H
#define SPAWN_PLAYER_HANDLER_H

#include "../../../../../common/src/main/packets/packet.h"
#include "../audio/game_sound.h"
#include "../map/map.h"
#include "packet_handler.h"

class SpawnPlayerHandler : public PacketHandler {
 private:
 public:
  SpawnPlayerHandler();
  ~SpawnPlayerHandler();

  /* Returns if game should continue or not */
  bool handle(Packet& packet, Map& map, GameSound& sound) override;
};

#endif