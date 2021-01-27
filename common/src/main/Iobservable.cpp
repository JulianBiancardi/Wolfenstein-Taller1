#include "Iobservable.h"

IObservable::IObservable() {}

void IObservable::add_observer(IObserver* observer) {
  observers.push_back(observer);
}

void IObservable::remove_observer(IObserver* observer) {
  observers.remove(observer);
}

void IObservable::notify() {
  for (auto& observer : observers) {
    observer->update();
  }
}

IObservable::~IObservable() {}