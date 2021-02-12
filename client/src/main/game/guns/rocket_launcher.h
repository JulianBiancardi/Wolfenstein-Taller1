#ifndef ROCKET_LAUNCHER_H
#define ROCKET_LAUNCHER_H

<<<<<<< HEAD:client/src/main/game/guns/rocket_launcher.h
#include <memory>
#include <vector>

#include "../../../../../common/src/main/utils/base_map.h"
#include "../entities/identifiable_object.h"
#include "gun.h"
#include "hit.h"
=======
#include "gun.h"
>>>>>>> c45cc697f4d5663c99645f75f2a74d9b0743ad6b:client/src/main/guns/rocket_launcher/rocket_launcher.h

class RocketLauncher : public Gun {
 private:
  bool triggered;

  Hit shoot(Object& player, int& current_bullets, BaseMap& map,
            std::vector<std::weak_ptr<IdentifiableObject>>& players) override;

 public:
  RocketLauncher();
  ~RocketLauncher();

  Hit trigger(Object& player, int& current_bullets, BaseMap& map,
              std::vector<std::weak_ptr<IdentifiableObject>>& players) override;
  void untrigger() override;
};

#endif
