#ifndef CASTER_H
#define CASTER_H

class Caster {
 private:
 public:
  Caster();
  ~Caster();

  virtual void operator()() = 0;
};

#endif
