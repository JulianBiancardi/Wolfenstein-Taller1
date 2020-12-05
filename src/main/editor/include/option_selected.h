#ifndef OPTION_SELECTED_H
#define OPTION_SELECTED_H

class OptionSelected {
 public:
  OptionSelected();

  int getCurrent_id() const;
  void setCurrent_id(int value);

  ~OptionSelected();

 private:
  int current_id;
};

#endif  // OPTION_SELECTED_H