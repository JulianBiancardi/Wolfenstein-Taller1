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
  void dequeue(T& buffer);
  void enqueue(const T& value);
  ~BlockingQueue();
};

#include "blocking_queue.tpp"

#endif
