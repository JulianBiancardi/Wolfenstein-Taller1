#include "client_manager.h"

#include <utility>

ClientManager::ClientManager() : reception_queue() {}

ClientManager::~ClientManager() {}

int ClientManager::next_id = 1;

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

void ClientManager::send_to(int id, packet_t& packet) {
  if (clients.find(id) != clients.end()) {
    clients[id].send(packet);
  }
}

void ClientManager::send_to_all(packet_t& packet) {
  std::unordered_map<int, Client>::iterator iter;
  for (iter = clients.begin(); iter != clients.end(); iter++) {
    (*iter).second.send(packet);
  }
}

void ClientManager::end_connection(int id) {
  packet_t end_of_connection_packet;  // TODO Fill with the data
  send_to(id, end_of_connection_packet);
  clients.erase(id);
}

void ClientManager::end_all_connections() {
  packet_t end_of_connection_packet;  // TODO Fill with the data
  send_to_all(end_of_connection_packet);
  clients.clear();
}
