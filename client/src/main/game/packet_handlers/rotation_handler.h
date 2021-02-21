#ifndef ROTATION_HANDLER_H
#define ROTATION_HANDLER_H

#include "../../../../../common/src/main/packets/packet.h"
#include "../audio/game_sound.h"
#include "../map/map.h"
#include "packet_handler.h"

class RotationHandler : public PacketHandler {
 private:
 public:
  RotationHandler();
  ~RotationHandler();

  /* Returns if game should continue or not */
  bool handle(Packet& packet, Map& map, GameSound& sound) override;
};

#endif