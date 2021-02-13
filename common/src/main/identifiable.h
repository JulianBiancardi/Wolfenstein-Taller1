#ifndef IDENTIFIABLE_H
#define IDENTIFIABLE_H

class Identifiable {
 protected:
  const unsigned int id;

 public:
  explicit Identifiable(unsigned int id);

  /* Returns the id */
  unsigned int get_id() const;
};

#endif
