#ifndef ROTATION_HANDLER_H
#define ROTATION_HANDLER_H

#include "../../../../common/src/main/packets/packet.h"
#include "../map.h"
#include "packet_handler.h"
#include "../game.h"

class RotationHandler : public PacketHandler {
 private:
 public:
  RotationHandler();
  ~RotationHandler();

  void handle(Packet &packet, Map &map, GameSound &sound) override;
};

#endif