#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H

#include <condition_variable>
#include <deque>
#include <mutex>
#include <queue>
#include <vector>

template <class T>
class BlockingQueue {
 private:
  std::mutex mtx;
  std::queue<T, std::deque<T>> prot_q;
  std::condition_variable cv;

 public:
  BlockingQueue();

  ~BlockingQueue();

  /* Take an element from the front of the queue and store it into the buffer.
   * The thread is blocked until the operation can be satisfied.
   */
  void dequeue(T& buffer);

  /* Put an element into the back of the queue */
  void enqueue(const T& value);

  /* Take an element from the front of the queue and store it into the buffer.
   * Returns true is operation was successful, false otherwise.
   */
  bool poll(T& buffer);
};

#include "blocking_queue.tpp"

#endif
