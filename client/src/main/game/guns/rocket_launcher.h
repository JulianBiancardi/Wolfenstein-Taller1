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
  bool shot;

  Hit shoot(Object& player, BaseMap& map,
            std::vector<std::weak_ptr<IdentifiableObject>>& players) override;

 public:
  explicit RocketLauncher(unsigned int resource_id);
  ~RocketLauncher();

  Hit update(Object& player, bool trigger, BaseMap& map,
             std::vector<std::weak_ptr<IdentifiableObject>>& players) override;

  SDL_Rect* get_slice(void* extra) override;
};

#endif
