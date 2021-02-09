#ifndef CHANGE_GUN_HANDLER_H
#define CHANGE_GUN_HANDLER_H

#include "../../../../common/src/main/packets/packet.h"
#include "../map.h"
#include "packet_handler.h"

class ChangeGunHandler : public PacketHandler {
 private:
 public:
  ChangeGunHandler();
  ~ChangeGunHandler();

  void handle(Packet& packet, Map& map, GameSound& sound) override;
};

#endif