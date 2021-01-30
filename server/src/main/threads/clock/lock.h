#ifndef LOCK_H
#define LOCK_H

class Lock {
 private:
  std::mutex& mutex;

 public:
  explicit Lock(std::mutex& mutex) : mutex(mutex) { mutex.lock(); }
  ~Lock() { mutex.unlock(); }
};

#endif
