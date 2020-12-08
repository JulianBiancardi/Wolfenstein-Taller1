#ifndef OPTION_SELECTED_H
#define OPTION_SELECTED_H

#include <sys/types.h>

class OptionSelected {
 public:
  OptionSelected();

  size_t get_current_id() const;
  void set_current_id(size_t value);

  ~OptionSelected();

 private:
  size_t current_id;
};

#endif  // OPTION_SELECTED_H