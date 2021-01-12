#ifndef SEND_THREAD_H
#define SEND_THREAD_H

#include "../../../../common/src/main/data_structures/blocking_queue.h"
#include "../../../../common/src/main/events/event_info.h"
#include "../../../../common/src/main/socket/socket.h"
#include "../../../../common/src/main/threads/thread.h"

class SendToServerThread : public Thread {
 private:
  BlockingQueue<Event>* events_queue;
  Socket connected_socket;

 public:
  SendToServerThread(Socket& connected_socket,
                     BlockingQueue<Event>* events_queue);
  ~SendToServerThread();

  void run() override;
};

#endif
