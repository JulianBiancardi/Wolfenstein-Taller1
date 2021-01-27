#ifndef IOBSERVABLE_H
#define IOBSERVABLE_H

#include <list>

#include "Iobserver.h"

class IObservable {
 private:
  std::list<IObserver*> observers;

 public:
  IObservable();

  void add_observer(IObserver* observer);

  void remove_observer(IObserver* observer);

  void notify();

  ~IObservable();
};

#endif  // IOBSERVABLE_H