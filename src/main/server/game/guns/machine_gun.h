#ifndef WOLFENSTEIN_TALLER1_MACHINE_GUN_H
#define WOLFENSTEIN_TALLER1_MACHINE_GUN_H

#include "../player.h"
#include "gun.h"

class MachineGun: public Gun {
    public:
        MachineGun();
        void shoot(Player &shooter) override;

    private:
        int range;
};


#endif //WOLFENSTEIN_TALLER1_MACHINE_GUN_H
