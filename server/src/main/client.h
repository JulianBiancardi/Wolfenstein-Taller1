#ifndef CLIENT_H
#define CLIENT_H

#include "../../../common/src/main/data_structures/blocking_queue.h"
#include "../../../common/src/main/packets/packet.h"
#include "../../../common/src/main/socket/socket.h"
#include "threads/receive_from_client_thread.h"
#include "threads/send_to_client_thread.h"

class Client {
 private:
  int id;
  Socket client_socket;
  BlockingQueue<packet_t> sending_queue;

  ReceiveFromClientThread* receiving_thread;
  SendToClientThread* sending_thread;

 public:
  explicit Client(int id, Socket& socket,
                  BlockingQueue<packet_t>& reception_queue);
  ~Client();

  void send(packet_t& packet);

  /* Returns true if the Client is still active, false otherwise */
  bool is_active();
};

#endif
