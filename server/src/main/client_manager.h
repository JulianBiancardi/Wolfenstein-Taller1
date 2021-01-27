#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include <memory>
#include <unordered_map>

#include "../../../common/src/main/data_structures/blocking_queue.h"
#include "client.h"

class ClientManager {
 private:
  unsigned int static next_id;
  std::unordered_map<unsigned int, std::unique_ptr<Client>> clients;
  BlockingQueue<Packet> reception_queue;

 public:
  ClientManager();
  ~ClientManager();

  /* Returns a reference to the client reception queue */
  BlockingQueue<Packet>& get_reception_queue();

  /* Adds a new client that will communicate with the server */
  void add_client(Socket& client_socket);

  /* Removes inactive clients */
  void clear();

  /* Sends a message to a client */
  void send_to(unsigned int id, Packet& packet);

  /* Sends a message to the given clients */
  void send_to_all(const std::vector<unsigned int>& ids, Packet& packet);

  /* Sends a message to all clients */
  void send_to_all(Packet& packet);

  /* Forcibly ends a connection with a client */
  void end_connection(unsigned int id);

  /* Forcibly ends a connection with all clients */
  void end_all_connections();
};

#endif
