#ifndef PROCESSOR_THREAD_H
#define PROCESSOR_THREAD_H

#include <atomic>

#include "../../../../common/src/main/threads/thread.h"
#include "../client_manager.h"
#include "../match_manager.h"

class ProcessorThread : public Thread {
 private:
  MatchManager match_manager;
  ClientManager& client_manager;
  std::atomic<bool> allowed_to_run;
  void run() override;

 public:
  ProcessorThread(ClientManager& client_manager);

  ProcessorThread(const ProcessorThread&) = delete;
  ProcessorThread& operator=(const ProcessorThread&) = delete;

  ProcessorThread(ProcessorThread&& other) = delete;
  ProcessorThread& operator=(ProcessorThread&& other) = delete;

  ~ProcessorThread();

  void force_stop();
};

#endif
