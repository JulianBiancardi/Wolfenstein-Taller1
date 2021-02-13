#ifndef RECEIVE_FROM_PEER_THREAD_H
#define RECEIVE_FROM_PEER_THREAD_H

#include <atomic>

#include "../../../../common/src/main/data_structures/blocking_queue.h"
#include "../../../../common/src/main/packets/packet.h"
#include "../../../../common/src/main/socket/socket.h"
#include "../../../../common/src/main/threads/thread.h"

class ReceiveFromPeerThread : public Thread {
 private:
  unsigned int client_id;
  Socket& connected_socket;
  BlockingQueue<Packet>& reception_queue;
  std::atomic<bool> allowed_to_run;
  std::atomic<bool> running;
  void run() override;

 public:
  explicit ReceiveFromPeerThread(Socket& connected_socket,
                                 BlockingQueue<Packet>& reception_queue);
  explicit ReceiveFromPeerThread(unsigned int client_id,
                                 Socket& connected_socket,
                                 BlockingQueue<Packet>& reception_queue);
  ~ReceiveFromPeerThread();

  void set_id(unsigned int id);
  bool is_running();
  bool is_active();
  void force_stop();
};

#endif
