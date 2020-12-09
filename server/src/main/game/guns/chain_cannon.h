#ifndef WOLFENSTEIN_TALLER1_CHAIN_CANNON_H
#define WOLFENSTEIN_TALLER1_CHAIN_CANNON_H

#include "gun.h"

class ChainCannon : public Gun{
    public:
        ChainCannon();
        int shoot(int &available_bullets) override;

    private:
    const static int bullet_required;
    const static int base_precision;
};


#endif //WOLFENSTEIN_TALLER1_CHAIN_CANNON_H
