#ifndef CLIENT_H
#define CLIENT_H

#include "../../../common/src/main/data_structures/blocking_queue.h"
#include "../../../common/src/main/packets/packet.h"
#include "../../../common/src/main/socket/socket.h"
#include "../../../common/src/main/threads/receive_from_peer_thread.h"
#include "../../../common/src/main/threads/send_to_peer_thread.h"

class Client {
 private:
  unsigned int id;
  Socket client_socket;
  BlockingQueue<Packet> sending_queue;

  ReceiveFromPeerThread receiving_thread;
  SendToPeerThread sending_thread;

  /* Acknowledge client of his ID */
  void sync();

 public:
  explicit Client(unsigned int id, Socket& socket,
                  BlockingQueue<Packet>& reception_queue);

  Client(const Client& other) = delete;
  Client& operator=(const Client&) = delete;

  Client(Client&& other) = delete;
  Client& operator=(Client&& other) = delete;

  ~Client();

  /* Sends a message to the client */
  void send(Packet& packet);

  /* Returns true if the Client is still active, false otherwise */
  bool is_active();
};

#endif
