#ifndef SPAWN_PLAYER_HANDLER_H
#define SPAWN_PLAYER_HANDLER_H

#include "../../../../common/src/main/packets/packet.h"
#include "../game.h"
#include "../map.h"
#include "packet_handler.h"

class SpawnPlayerHandler : public PacketHandler {
 private:
 public:
  SpawnPlayerHandler();
  ~SpawnPlayerHandler();

  void handle(Packet &packet, Map &map, GameSound &sound) override;
};

#endif