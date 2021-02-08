#ifndef PISTOL_H
#define PISTOL_H

#include "../player.h"
#include "gun.h"
#include "hit.h"
#include "spray.h"

class Pistol : public Gun {
 private:
  Spray spray;

  double linear_func(double x);
  double slope;
  double intercept;
  bool triggered;

  Hit shoot(Object& player, int& current_bullets, BaseMap& map,
            const std::vector<std::shared_ptr<Object>>& objects) override;

 public:
  Pistol();
  ~Pistol();

  Hit trigger(Object& player, int& current_bullets, BaseMap& map,
              const std::vector<std::shared_ptr<Object>>& objects) override;
  void untrigger() override;
};

#endif
