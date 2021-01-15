#ifndef IDENTIFIABLE_H
#define IDENTIFIABLE_H

class Identifiable {
 private:
  static int next_id;
  int const id;

 public:
  Identifiable();
  explicit Identifiable(int id);

  int get_id();
};

#endif
