#ifndef THREAD_H
#define THREAD_H

#include <thread>

class Thread {
 protected:
  std::thread thread;
  virtual void run() = 0;

 public:
  Thread();

  Thread(const Thread&) = delete;
  Thread& operator=(const Thread&) = delete;

  // Thread movement isn't allowed
  Thread(Thread&& other) = delete;
  Thread& operator=(Thread&& other) = delete;

  virtual ~Thread();

  /* Executes the Thread. */
  void start();

  /* Joins the thread. */
  void join();
};

#endif
