#ifndef MOVE_HANDLER_H
#define MOVE_HANDLER_H

#include "../../../../common/src/main/packets/packet.h"
#include "../map.h"
#include "packet_handler.h"

class MoveHandler : public PacketHandler {
 private:
 public:
  MoveHandler();
  ~MoveHandler();

  void handle(Packet& packet, Map& map) override;
};

#endif
