#ifndef SERVER_H
#define SERVER_H

#include "../../../common/src/main/data_structures/blocking_queue.h"
#include "../../../common/src/main/data_structures/protected_queue.h"
#include "../../../common/src/main/packets/packet.h"
#include "../../../common/src/main/socket/socket.h"
#include "threads/receive_from_server_thread.h"
#include "threads/send_to_server_thread.h"

class Server {
 private:
  unsigned char id;
  Socket server_socket;
  BlockingQueue<Packet> sending_queue;
  ProtectedQueue<Packet> reception_queue;

  ReceiveFromServerThread receiving_thread;
  SendToServerThread sending_thread;

  void sync_with_server(Socket& server_socket);

 public:
  Server();
  ~Server();

  void send(Packet& packet);
  unsigned char get_id();
};

#endif
