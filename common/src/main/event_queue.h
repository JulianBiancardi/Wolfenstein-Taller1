#ifndef WOLFENSTEIN_TALLER1_SRC_MAIN_EVENT_QUEUE_H_
#define WOLFENSTEIN_TALLER1_SRC_MAIN_EVENT_QUEUE_H_
#include <queue>
#include <mutex>
#include <condition_variable>

template<class T>
class EventQueue {
 private:
  std::queue<T> queue;
  std::mutex mutex;
  std::condition_variable cv;
  EventQueue(const EventQueue &) = delete;
  EventQueue &operator=(const EventQueue &) = delete;

 public:
  EventQueue() {}
  ~EventQueue() {}

  void enqueue(const T &val);

  T dequeue();

  const bool is_empty();

};

template<class T>
void EventQueue<T>::enqueue(const T &val) {
  std::lock_guard<std::mutex> lock(mutex);
  if (queue.empty()) {
    //Se envia una señal a todos los hilos que, en caso de que la cola
    // esté vacía, están esperando la acción de encolar.
    cv.notify_all();
  }
  queue.push(val);
}

template<class T>
T EventQueue<T>::dequeue() {
  std::unique_lock<std::mutex> lock(mutex);
  if (queue.empty()) {
    //Esperamos a que otros hilos hagan un enqueue.
    cv.wait(lock);
  }
  T ret_value = queue.front();
  queue.pop();
  return ret_value;

}
template<class T>
const bool EventQueue<T>::is_empty() {
  std::lock_guard<std::mutex> lock(mutex);
  return queue.empty();
}

#endif //WOLFENSTEIN_TALLER1_SRC_MAIN_EVENT_QUEUE_H_
