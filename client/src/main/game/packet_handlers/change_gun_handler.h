#ifndef CHANGE_GUN_HANDLER_H
#define CHANGE_GUN_HANDLER_H

#include "../../../../../common/src/main/packets/packet.h"
#include "../audio/game_sound.h"
#include "../map/map.h"
#include "packet_handler.h"

class ChangeGunHandler : public PacketHandler {
 private:
 public:
  ChangeGunHandler();
  ~ChangeGunHandler();

  /* Returns if game should continue or not */
  bool handle(Packet& packet, Map& map, GameSound& sound) override;
};

#endif