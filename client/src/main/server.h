#ifndef SERVER_H
#define SERVER_H

#include "../../../common/src/main/data_structures/blocking_queue.h"
#include "../../../common/src/main/packets/packet.h"
#include "../../../common/src/main/socket/socket.h"
#include "../../../common/src/main/threads/receive_from_peer_thread.h"
#include "../../../common/src/main/threads/send_to_peer_thread.h"

class Server {
 private:
  unsigned int id;
  Socket server_socket;
  BlockingQueue<Packet> sending_queue;
  BlockingQueue<Packet> reception_queue;

  ReceiveFromPeerThread receiving_thread;
  SendToPeerThread sending_thread;

  void sync_with_server(Socket& server_socket);

 public:
  Server();
  ~Server();

  /* Returns a reference to the client reception queue */
  BlockingQueue<Packet>& get_reception_queue();

  /* Sends a message to the client */
  void send(Packet& packet);

  /* Returns the id the server assigned to the the client */
  unsigned int get_id();
};

#endif
