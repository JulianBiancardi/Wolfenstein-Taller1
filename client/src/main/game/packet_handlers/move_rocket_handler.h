#ifndef MOVE_ROCKET_HANDLER_H
#define MOVE_ROCKET_HANDLER_H

#include "../../../../../common/src/main/packets/packet.h"
#include "../audio/game_sound.h"
#include "../map/map.h"
#include "packet_handler.h"

class MoveRocketHandler : public PacketHandler {
 private:
 public:
  MoveRocketHandler();
  ~MoveRocketHandler();

  /* Returns if game should continue or not */
  bool handle(Packet& packet, Map& map, GameSound& sound) override;
};

#endif
