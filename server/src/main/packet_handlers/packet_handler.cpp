#include "packet_handler.h"

#include "../../../../common/src/main/packets/packing.h"

PacketHandler::PacketHandler() {}

PacketHandler::~PacketHandler() {}

void PacketHandler::consequent_grab(unsigned int player_id, Match& match,
                                    ClientManager& client_manager) {
  unsigned int item_id = match.grab_item(player_id);

  if (item_id != 0) {
    unsigned char data[GRAB_SIZE];
    size_t size = pack(data, "CII", GRAB, &player_id, &item_id);
    Packet packet(size, data);

    const std::unordered_set<unsigned int>& clients = match.get_players_ids();
    client_manager.send_to_all(clients, packet);
  }
}

void PacketHandler::game_over(Match& match, ClientManager& client_manager) {
  unsigned char match_id = match.get_id();

  unsigned char data[GAME_OVER_SIZE];
  size_t size = pack(data, "CC", GAME_OVER, &match_id);
  Packet packet(size, data);

  BlockingQueue<Packet>& reception_queue = client_manager.get_reception_queue();
  reception_queue.enqueue(packet);
}
