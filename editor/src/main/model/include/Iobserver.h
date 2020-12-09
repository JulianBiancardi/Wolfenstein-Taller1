#ifndef IOBSERVER_H
#define IOBSERVER_H

class IObserver {
 private:
 public:
  IObserver() {}

  virtual void update() = 0;

  ~IObserver() {}
};

#endif  // IOBSERVER_H