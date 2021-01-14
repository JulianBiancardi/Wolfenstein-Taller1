#ifndef RECEIVE_FROM_SERVER_THREAD_H
#define RECEIVE_FROM_SERVER_THREAD_H

#include "../../../../common/src/main/data_structures/protected_queue.h"
#include "../../../../common/src/main/packets/packet.h"
#include "../../../../common/src/main/socket/socket.h"
#include "../../../../common/src/main/threads/thread.h"

class ReceiveFromServerThread : public Thread {
 private:
  Socket& connected_socket;
  ProtectedQueue<packet_t>* reception_queue;
  bool allowed_to_run;
  bool running;

 public:
  ReceiveFromServerThread(Socket& connected_socket,
                          ProtectedQueue<packet_t>* reception_queue);
  ~ReceiveFromServerThread();

  void run() override;
};

#endif