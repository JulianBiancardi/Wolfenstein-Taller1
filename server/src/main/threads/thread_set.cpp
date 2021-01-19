#include "thread_set.h"

ThreadSet::ThreadSet() {}

ThreadSet::~ThreadSet() {
  std::unordered_set<ReceiveFromClientThread*>::iterator it;
  for (it = threads.begin(); it != threads.end(); ++it) {
    (*it)->force_stop();
    (*it)->join();
    delete *it;
  }
}

void ThreadSet::clear() {
  std::unordered_set<ReceiveFromClientThread*> threads_kept;

  std::unordered_set<ReceiveFromClientThread*>::iterator it;
  for (it = threads.begin(); it != threads.end(); ++it) {
    if ((*it)->is_running()) {
      threads_kept.insert(*it);
    } else {
      (*it)->join();
      delete *it;
    }
  }

  threads.swap(threads_kept);
}

void ThreadSet::insert(ReceiveFromClientThread* thread) {
  threads.insert(thread);
}
