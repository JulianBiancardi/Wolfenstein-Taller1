#ifndef GAME_OVER_HANDLER_H
#define GAME_OVER_HANDLER_H

#include "../../../../../common/src/main/packets/packet.h"
#include "../audio/game_sound.h"
#include "../map/map.h"
#include "packet_handler.h"

class GameOverHandler : public PacketHandler {
 private:
 public:
  GameOverHandler();
  ~GameOverHandler();

  /* Returns if game should continue or not */
  bool handle(Packet& packet, Map& map, GameSound& sound) override;
};

#endif
