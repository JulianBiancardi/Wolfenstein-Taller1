#ifndef PROCESSOR_THREAD_H
#define PROCESSOR_THREAD_H

#include <atomic>

#include "../../../../common/src/main/threads/thread.h"
#include "../client_manager.h"
#include "../match_manager.h"

class ProcessorThread : public Thread {
 private:
  // This class could maybe be the owner
  MatchManager& match_manager;
  ClientManager& client_manager;
  BlockingQueue<Packet>& reception_queue;
  std::atomic<bool> allowed_to_run;
  void run() override;

 public:
  ProcessorThread(MatchManager& match_manager, ClientManager& client_manager,
                  BlockingQueue<Packet>& reception_queue);

  ProcessorThread(const ProcessorThread&) = delete;
  ProcessorThread& operator=(const ProcessorThread&) = delete;

  ProcessorThread(ProcessorThread&& other) = delete;
  ProcessorThread& operator=(ProcessorThread&& other) = delete;

  ~ProcessorThread();
};

#endif
