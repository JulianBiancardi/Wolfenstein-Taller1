#ifndef DAMAGABLE_H
#define DAMAGABLE_H

class Damagable {
 public:
  virtual void receive_damage(int amount) = 0;
};

#endif
