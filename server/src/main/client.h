#ifndef CLIENT_H
#define CLIENT_H

#include "../../../common/src/main/data_structures/blocking_queue.h"
#include "../../../common/src/main/packets/packet.h"
#include "../../../common/src/main/socket/socket.h"
#include "threads/receive_from_client_thread.h"
#include "threads/send_to_client_thread.h"

class Client {
 private:
  unsigned int id;
  Socket client_socket;
  BlockingQueue<Packet> sending_queue;

  ReceiveFromClientThread* receiving_thread;
  SendToClientThread* sending_thread;

 public:
  explicit Client(unsigned int id, Socket& socket,
                  BlockingQueue<Packet>& reception_queue);
  ~Client();

  /* Sends a message to the client */
  void send(Packet& packet);

  /* Returns true if the Client is still active, false otherwise */
  bool is_active();
};

#endif
