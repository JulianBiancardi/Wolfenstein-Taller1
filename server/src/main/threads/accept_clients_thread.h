#ifndef ACCEPT_CLIENTS_THREAD_H
#define ACCEPT_CLIENTS_THREAD_H

#include <atomic>

#include "../../../../common/src/main/data_structures/blocking_queue.h"
#include "../../../../common/src/main/socket/socket.h"
#include "../../../../common/src/main/threads/thread.h"

class AcceptClientsThread : public Thread {
 private:
  Socket acceptor_socket;
  BlockingQueue<packet_t>* reception_queue;
  std::atomic<bool> allowed_to_run;
  void run() override;

 public:
  AcceptClientsThread(Socket& acceptor_socket,
                      BlockingQueue<packet_t>* reception_queue);

  AcceptClientsThread(const AcceptClientsThread&) = delete;
  AcceptClientsThread& operator=(const AcceptClientsThread&) = delete;

  AcceptClientsThread(AcceptClientsThread&& other) = delete;
  AcceptClientsThread& operator=(AcceptClientsThread&& other) = delete;

  ~AcceptClientsThread();

  /* Forces the thread to stop, allowing a join briefly after */
  void force_stop();
};

#endif
