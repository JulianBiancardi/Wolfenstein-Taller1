#ifndef UPDATEABLE_H
#define UPDATEABLE_H

class Updateable {
 private:
 public:
  Updateable();
  ~Updateable();

  virtual void update() = 0;
};

#endif
