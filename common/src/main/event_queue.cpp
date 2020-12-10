#include "event_queue.h"
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
const T & EventQueue<T>::dequeue() {
  std::unique_lock<std::mutex> lock(mutex);
  if (queue.empty()) {
    //Esperamos a que otros hilos hagan un enqueue.
    cv.wait(lock);
  }
  const T& ret_value = queue.front();
  queue.pop();
  return ret_value;

}
template<class T>
const bool EventQueue<T>::is_empty() const {
  std::lock_guard<std::mutex> lock(mutex);
  return queue.empty();
}