#ifndef WOLFENSTEIN_TALLER1_MACHINE_GUN_H
#define WOLFENSTEIN_TALLER1_MACHINE_GUN_H

//#include "../player.h"
#include "gun.h"

class MachineGun: public Gun {
    public:
        MachineGun();
        void shoot(Player &shooter) override;

    private:
        const static int bullet_required;
        const static int base_precision;
};


#endif //WOLFENSTEIN_TALLER1_MACHINE_GUN_H