#ifndef MOVE_HANDLER_H
#define MOVE_HANDLER_H

#include "../../../../common/src/main/packets/packet.h"
#include "../map.h"
#include "packet_handler.h"

class MovementHandler : public PacketHandler {
 private:
 public:
  MovementHandler();
  ~MovementHandler();

  void handle(Packet &packet, Map &map, GameSound &sound) override;
};

#endif
