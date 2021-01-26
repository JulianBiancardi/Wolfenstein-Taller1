#ifndef SEND_TO_PEER_THREAD_H
#define SEND_TO_PEER_THREAD_H

#include "../../../../common/src/main/data_structures/blocking_queue.h"
#include "../../../../common/src/main/packets/packet.h"
#include "../../../../common/src/main/socket/socket.h"
#include "../../../../common/src/main/threads/thread.h"

class SendToPeerThread : public Thread {
 private:
  unsigned char client_id;
  BlockingQueue<Packet>& sending_queue;
  Socket& connected_socket;
  bool allowed_to_run;
  bool running;

 public:
  SendToPeerThread(unsigned int client_id, Socket& connected_socket,
                   BlockingQueue<Packet>& events_queue);
  ~SendToPeerThread();

  bool is_running();
  void force_stop();
  void run() override;
};

#endif
