template <class T>
BlockingQueue<T>::BlockingQueue() : prot_q() {}

template <class T>
BlockingQueue<T>::~BlockingQueue() {}

template <class T>
void BlockingQueue<T>::dequeue(T& buffer) {
  std::unique_lock<std::mutex> lock(mtx);
  if (prot_q.empty()) {
    cv.wait(lock);
  }
  buffer = prot_q.front();
  prot_q.pop();
}

template <class T>
void BlockingQueue<T>::enqueue(const T& value) {
  {
    std::unique_lock<std::mutex> lock(mtx);
    prot_q.push(value);
  }
  cv.notify_one();
}
