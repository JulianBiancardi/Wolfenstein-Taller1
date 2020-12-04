#ifndef OPTIONSELECTED_H
#define OPTIONSELECTED_H

class OptionSelected {
 public:
  OptionSelected();

  int getCurrent_id() const;
  void setCurrent_id(int value);

  ~OptionSelected();

 private:
  int current_id;
};

#endif  // OPTIONSELECTED_H