#ifndef PROTECTED_Q_CPP
#define PROTECTED_Q_CPP

#include <deque>
#include <mutex>
#include <queue>
#include <vector>

template <class T>
class ProtectedQueue {
 private:
  std::mutex mtx;
  std::queue<T, std::deque<T>> prot_q;

 public:
  ProtectedQueue();
  explicit ProtectedQueue(std::vector<T>& vector);
  bool empty();
  void dequeue(T& buffer);
  void enqueue(const T& value);
  T& front();
  ~ProtectedQueue();
};

#include "protected_queue.tpp"

#endif