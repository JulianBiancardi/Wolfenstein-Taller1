#ifndef CELD_H
#define CELD_H

#include <sys/types.h>

#include "Iobservable.h"

class Celd : public IObservable {
 private:
  size_t id;

 public:
  Celd();

  size_t get_id() const;
  void set_id(size_t value);
  void clear();
  bool is_empty() const;

  ~Celd();
};

#endif  // CELD_H