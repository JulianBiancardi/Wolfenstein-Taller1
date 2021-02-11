#include "add_item_handler.h"

#include "../../../../../common/src/main/packets/packing.h"

AddItemHandler::AddItemHandler() = default;

AddItemHandler::~AddItemHandler() = default;

void AddItemHandler::handle(Packet& packet, Map& map, GameSound& sound) {
  unsigned char type;
  unsigned int item_id;
  unsigned int item_type;
  unsigned char posX;
  unsigned char posY;
  unpack(packet.get_data(), "CICCC", &type, &item_id, &item_type, &posX, &posY);
  map.add_item(item_id, item_type, Point(posX + 0.5, posY + 0.5));
}
