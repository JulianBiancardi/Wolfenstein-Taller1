#ifndef WOLFENSTEIN_TALLER1_ROCKET_LAUNCHER_H
#define WOLFENSTEIN_TALLER1_ROCKET_LAUNCHER_H



#include "gun.h"

class RocketLauncher : public Gun {
    public:
    RocketLauncher();
        void shoot(Player &shooter) override;
    private:
        int range;
};



#endif //WOLFENSTEIN_TALLER1_ROCKET_LAUNCHER_H
