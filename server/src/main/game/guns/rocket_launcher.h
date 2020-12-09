#ifndef WOLFENSTEIN_TALLER1_ROCKET_LAUNCHER_H
#define WOLFENSTEIN_TALLER1_ROCKET_LAUNCHER_H
#include "gun.h"

class RocketLauncher : public Gun {
    public:
        RocketLauncher();
        int shoot(/*Player &shooter*/int &current_bullets) override;

    private:
        const static int bullet_required;
        const static int base_precision;
};



#endif //WOLFENSTEIN_TALLER1_ROCKET_LAUNCHER_H