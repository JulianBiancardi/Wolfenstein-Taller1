#ifndef WOLFENSTEIN_TALLER1_GUN_H
#define WOLFENSTEIN_TALLER1_GUN_H
#include <random>
#include "../../config_loader.h"
#include "../player.h"

class Gun {
    public:
        Gun();
        virtual void shoot(Player& shooter);
};
#endif //WOLFENSTEIN_TALLER1_GUN_H
