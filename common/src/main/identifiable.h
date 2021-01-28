#ifndef IDENTIFIABLE_H
#define IDENTIFIABLE_H

class Identifiable {
 private:
  static int next_id;

 protected:
  int const id;

 public:
  Identifiable();
  explicit Identifiable(int id);
  void static reset_id();  // Only used for testing

  int get_id() const;
};

#endif
