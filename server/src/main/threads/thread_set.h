#ifndef THREAD_VECTOR_H
#define THREAD_VECTOR_H

#include <unordered_set>

#include "receive_from_client_thread.h"

/* Designed specifically for ReceiveFromClientThread,
 * instead of Thread, since Thread is more basic and this
 * is quite specific on the methods
 */
class ThreadSet {
 private:
  std::unordered_set<ReceiveFromClientThread*> threads;

 public:
  ThreadSet();
  ~ThreadSet();

  /* Removes from the Set the Threads which have stopped running. */
  void clear();

  /* Inserts a new Thread into the Set */
  void insert(ReceiveFromClientThread* thread);
};

#endif
