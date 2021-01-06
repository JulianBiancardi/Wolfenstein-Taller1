#ifndef IDENTIFIABLE_H
#define IDENTIFIABLE_H

class Identifiable {
 protected:
  int id;

 public:
  Identifiable(int id) : id(id) {}

  int get_id() { return id; }
};

#endif
