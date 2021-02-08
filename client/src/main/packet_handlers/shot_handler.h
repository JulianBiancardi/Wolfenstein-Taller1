#ifndef SHOT_HANDLER_H
#define SHOT_HANDLER_H

#include "../../../../common/src/main/packets/packet.h"
#include "../game.h"
#include "../map.h"
#include "packet_handler.h"

class ShotHandler : public PacketHandler {
 private:
 public:
  ShotHandler();
  ~ShotHandler();

  void handle(Packet &packet, Map &map, GameSound &sound) override;
};

#endif