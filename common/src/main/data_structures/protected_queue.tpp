template <class T>
ProtectedQueue<T>::ProtectedQueue() : prot_q() {}

template <class T>
ProtectedQueue<T>::ProtectedQueue(std::vector<T>& vector)
    : prot_q(std::deque<T>(vector.begin(), vector.end())) {}

template <class T>
ProtectedQueue<T>::~ProtectedQueue() {}

template <class T>
void ProtectedQueue<T>::dequeue(T& buffer) {
  std::lock_guard<std::mutex> lock(mtx);
  if (!prot_q.empty()) {
    buffer = prot_q.front();
    prot_q.pop();
  }
}

template <class T>
void ProtectedQueue<T>::enqueue(const T& value) {
  std::lock_guard<std::mutex> lock(mtx);
  prot_q.push(value);
}

template <class T>
bool ProtectedQueue<T>::empty() {
  std::lock_guard<std::mutex> lock(mtx);
  return prot_q.empty();
}

template <class T>
T& ProtectedQueue<T>::front() {
  std::lock_guard<std::mutex> lock(mtx);
  return prot_q.front();
}
