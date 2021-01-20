#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include <unordered_map>

#include "../../../common/src/main/data_structures/blocking_queue.h"
#include "client.h"

class ClientManager {
 private:
  int static next_id;
  std::unordered_map<int, Client> clients;
  BlockingQueue<packet_t> reception_queue;

 public:
  ClientManager();
  ~ClientManager();

  /* Adds a new client that will communicate with the server */
  void add_client(Socket& client_socket);

  /* Removes inactive clients */
  void clear();

  /* Sends a message to a client */
  void send_to(int id, packet_t& packet);

  /* Sends a message to all clients */
  void send_to_all(packet_t& packet);

  /* Forcibly ends a connection with a client */
  void end_connection(int id);

  /* Forcibly ends a connection with all clients */
  void end_all_connections();
};

#endif
