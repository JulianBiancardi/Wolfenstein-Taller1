#ifndef ADD_ITEM_HANLDER_H
#define ADD_ITEM_HANLDER_H

#include "../../../../../common/src/main/packets/packet.h"
#include "../audio/game_sound.h"
#include "../map/map.h"
#include "packet_handler.h"

class AddItemHandler : public PacketHandler {
 private:
 public:
  AddItemHandler();
  ~AddItemHandler();

  void handle(Packet& packet, Map& map, GameSound& sound) override;
};

#endif
