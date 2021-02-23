#include "close_door_handler.h"

#include "../../../../common/src/main/packets/packing.h"

CloseDoorHandler::CloseDoorHandler() {}

CloseDoorHandler::~CloseDoorHandler() {}

void CloseDoorHandler::handle(Packet& packet, ClientManager& client_manager,
                              MatchManager& match_manager) {
  unsigned char type;
  unsigned int x;
  unsigned int y;
  unsigned char match_id;
  unpack(packet.get_data(), "CIIC", &type, &x, &y, &match_id);

  Match& match = match_manager.get_match(match_id);

  if (match.close_door(std::make_pair(x, y))) {
    const std::unordered_set<unsigned int>& clients = match.get_players_ids();

    unsigned char data[DOOR_UPDATE_SIZE];
    size_t size = pack(data, "CICIIC", DOOR_UPDATE, 0, match_id, x, y, false);
    Packet door_update_packet(size, data);
    client_manager.send_to_all(clients, door_update_packet);
  }
}
