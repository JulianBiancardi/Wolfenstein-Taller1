#ifndef RECEIVE_FROM_CLIENT_THREAD_H
#define RECEIVE_FROM_CLIENT_THREAD_H

#include "../../../../common/src/main/data_structures/blocking_queue.h"
#include "../../../../common/src/main/packets/packet.h"
#include "../../../../common/src/main/socket/socket.h"
#include "../../../../common/src/main/threads/thread.h"

class ReceiveFromClientThread : public Thread {
 private:
  Socket& connected_socket;
  BlockingQueue<Packet>& reception_queue;
  bool allowed_to_run;
  bool running;

 public:
  explicit ReceiveFromClientThread(Socket& connected_socket,
                                   BlockingQueue<Packet>& reception_queue);
  ~ReceiveFromClientThread();

  void run() override;
  bool is_running();
  void force_stop();
};

#endif
