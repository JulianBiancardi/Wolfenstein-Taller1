#include "client_manager.h"

#include <utility>

#include "../../../../common/src/main/packets/packing.h"

ClientManager::ClientManager() : clients(), reception_queue() {}

ClientManager::~ClientManager() {}

unsigned int ClientManager::next_id = 1;

BlockingQueue<Packet>& ClientManager::get_reception_queue() {
  return reception_queue;
}

void ClientManager::add_client(Socket& client_socket) {
  std::unique_ptr<Client> client(
      new Client(next_id, client_socket, reception_queue));
  clients.insert(std::make_pair(next_id, std::move(client)));
  next_id++;
}

void ClientManager::clear() {
  std::unordered_map<unsigned int, std::unique_ptr<Client>> clients_kept;

  std::unordered_map<unsigned int, std::unique_ptr<Client>>::iterator iter;
  for (iter = clients.begin(); iter != clients.end(); iter++) {
    if (iter->second->is_active()) {
      clients_kept.insert(*iter);
    }
    // TODO Check for leaks. We might need to specially clear a Client
  }

  clients.swap(clients_kept);
}

void ClientManager::send_to(unsigned int id, Packet& packet) {
  if (clients.find(id) != clients.end()) {
    clients.at(id)->send(packet);
  }
}

void ClientManager::send_to_all(const std::vector<unsigned int>& ids,
                                Packet& packet) {
  std::vector<unsigned int>::const_iterator iter;
  for (iter = ids.begin(); iter != ids.end(); iter++) {
    send_to(*iter, packet);
  }
}

void ClientManager::send_to_all(Packet& packet) {
  std::unordered_map<unsigned int, std::unique_ptr<Client>>::iterator iter;
  for (iter = clients.begin(); iter != clients.end(); iter++) {
    iter->second->send(packet);
  }
}

void ClientManager::end_connection(unsigned int id) {
  if (clients.find(id) != clients.end()) {
    unsigned char data[END_OF_CONNECTION_SIZE];
    size_t size = pack(data, "CI", END_OF_CONNECTION, id);
    Packet packet(size, data);
    clients.at(id)->send(packet);
    clients.erase(id);
  }
}

void ClientManager::end_all_connections() {
  std::unordered_map<unsigned int, std::unique_ptr<Client>>::iterator iter;
  for (iter = clients.begin(); iter != clients.end(); iter++) {
    unsigned char data[END_OF_CONNECTION_SIZE];
    size_t size = pack(data, "CI", END_OF_CONNECTION, iter->first);
    Packet packet(size, data);
    iter->second->send(packet);
  }
  clients.clear();
}
