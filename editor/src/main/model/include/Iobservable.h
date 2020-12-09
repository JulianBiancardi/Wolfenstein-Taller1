#ifndef IOBSERVABLE_H
#define IOBSERVABLE_H

#include <list>

#include "Iobserver.h"

class IObservable {
 private:
  std::list<IObserver*> observers;

 public:
  IObservable() {}

  void add_observer(IObserver* observer) {
    this->observers.push_back(observer);
  }

  void notify() {
    for (auto& observer : observers) {
      observer->update();
    }
  }

  ~IObservable() {}
};

#endif  // IOBSERVABLE_H