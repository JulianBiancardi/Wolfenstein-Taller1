#ifndef ROCKET_LAUNCHER_H
#define ROCKET_LAUNCHER_H

#include <memory>
#include <vector>

#include "../../../../../common/src/main/utils/base_map.h"
#include "../entities/identifiable_object.h"
#include "gun.h"
#include "hit.h"

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

  Image* get_image(ResourceManager& resource_manager) override;
  SDL_Rect* get_slice(void* extra) override;
};

#endif
