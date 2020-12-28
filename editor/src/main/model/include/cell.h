#ifndef CELL_H
#define CELL_H

#include <sys/types.h>

#include "Iobservable.h"

class Cell : public IObservable {
 private:
  size_t id;

 public:
  Cell();

  size_t get_id() const;
  void set_id(size_t value);
  void clear();
  bool is_empty() const;

  ~Cell();
};

#endif  // CELL_H