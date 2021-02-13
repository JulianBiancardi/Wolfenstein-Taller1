#ifndef SEND_TO_PEER_THREAD_H
#define SEND_TO_PEER_THREAD_H

#include <atomic>

#include "../../../../common/src/main/data_structures/blocking_queue.h"
#include "../../../../common/src/main/packets/packet.h"
#include "../../../../common/src/main/socket/socket.h"
#include "../../../../common/src/main/threads/thread.h"

class SendToPeerThread : public Thread {
 private:
  unsigned int client_id;
  Socket& connected_socket;
  BlockingQueue<Packet>& sending_queue;
  std::atomic<bool> allowed_to_run;
  std::atomic<bool> running;
  void run() override;

 public:
  explicit SendToPeerThread(Socket& connected_socket,
                            BlockingQueue<Packet>& events_queue);
  explicit SendToPeerThread(unsigned int client_id, Socket& connected_socket,
                            BlockingQueue<Packet>& events_queue);
  ~SendToPeerThread();

  void set_id(unsigned int id);
  bool is_running();
  void force_stop();
};

#endif
