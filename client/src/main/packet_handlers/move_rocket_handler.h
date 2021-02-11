#ifndef MOVE_ROCKET_HANDLER_H
#define MOVE_ROCKET_HANDLER_H

#include "../../../../common/src/main/packets/packet.h"
#include "../map.h"
#include "packet_handler.h"

class MoveRocketHandler : public PacketHandler {
 private:
 public:
  MoveRocketHandler();
  ~MoveRocketHandler();

  void handle(Packet& packet, Map& map, GameSound& sound) override;
};

#endif
