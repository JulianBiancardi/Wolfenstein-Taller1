#ifndef CELL_H
#define CELL_H

#include <sys/types.h>

#include "Iobservable.h"

class Cell : public IObservable {
 private:
  size_t id;
  size_t type;

 public:
  Cell();

  size_t get_id() const;
  size_t get_type() const;
  void set_data(size_t id, size_t type);
  void clear();
  bool is_empty() const;

  ~Cell();
};

#endif  // CELL_H