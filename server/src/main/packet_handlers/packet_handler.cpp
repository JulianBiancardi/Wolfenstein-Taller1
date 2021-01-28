#include "packet_handler.h"

#include "../../../../common/src/main/packets/packing.h"

PacketHandler::PacketHandler() {}

PacketHandler::~PacketHandler() {}

void PacketHandler::consequent_grab(unsigned char player_id, Match& match,
                                    ClientManager& client_manager) {
  unsigned int item_id = match.grab_item(player_id);

  if (item_id != 0) {
    unsigned char data[GRAB_SIZE];
    size_t size = pack(data, "CII", GRAB, &player_id, &item_id);
    Packet packet(size, data);

    const std::unordered_set<unsigned int>
        & client_ids = match.get_players_ids();
    client_manager.send_to_all(client_ids, packet);
  }
}
