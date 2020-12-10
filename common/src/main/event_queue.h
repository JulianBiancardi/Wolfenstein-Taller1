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

    void enqueue(const T& val);

    const T& dequeue();

    const bool is_empty() const;

};

#endif //WOLFENSTEIN_TALLER1_SRC_MAIN_EVENT_QUEUE_H_
