#include "grab_handler.h"

#include "../../../../common/src/main/packets/packing.h"

GrabHandler::GrabHandler() {}

GrabHandler::~GrabHandler() {}

void GrabHandler::handle(Packet &packet, Map &map, GameSound &sound) {
  unsigned char type;
  unsigned int player_id;
  unsigned int item_id;
  unpack(packet.get_data(), "CII", &type, &player_id, &item_id);

  map.pick_item(player_id, item_id);
}