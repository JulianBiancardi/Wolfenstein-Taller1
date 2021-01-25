#ifndef SEND_THREAD_H
#define SEND_THREAD_H

#include "../../../../common/src/main/data_structures/blocking_queue.h"
#include "../../../../common/src/main/packets/packet.h"
#include "../../../../common/src/main/socket/socket.h"
#include "../../../../common/src/main/threads/thread.h"

class SendToServerThread : public Thread {
 private:
  BlockingQueue<Packet>& events_queue;
  Socket& connected_socket;
  bool allowed_to_run;
  bool running;

 public:
  SendToServerThread(Socket& connected_socket,
                     BlockingQueue<Packet>& events_queue);
  ~SendToServerThread();

  void force_stop();
  bool is_running();
  void run() override;
};

#endif
