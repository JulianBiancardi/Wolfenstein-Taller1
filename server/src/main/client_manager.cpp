#include "client_manager.h"

#include <utility>

#include "../../../../common/src/main/packets/packing.h"

ClientManager::ClientManager() : reception_queue() {}

ClientManager::~ClientManager() {}

int ClientManager::next_id = 1;

BlockingQueue<Packet>& ClientManager::get_reception_queue() {
  return reception_queue;
}

void ClientManager::add_client(Socket& client_socket) {
  clients.emplace(next_id, Client(next_id, client_socket, reception_queue));
  next_id++;
}

void ClientManager::clear() {
  std::unordered_map<int, Client> clients_kept;

  std::unordered_map<int, Client>::iterator iter;
  for (iter = clients.begin(); iter != clients.end(); iter++) {
    if ((*iter).second.is_active()) {
      clients_kept.insert(*iter);
    }
    // TODO Check for leaks. We might need to specially clear a Client
  }

  clients.swap(clients_kept);
}

void ClientManager::send_to(int id, Packet& packet) {
  if (clients.find(id) != clients.end()) {
    clients[id].send(packet);
  }
}

void ClientManager::send_to_all(Packet& packet) {
  std::unordered_map<int, Client>::iterator iter;
  for (iter = clients.begin(); iter != clients.end(); iter++) {
    (*iter).second.send(packet);
  }
}

void ClientManager::end_connection(unsigned int id) { clients.erase(id); }

void ClientManager::end_all_connections() { clients.clear(); }
