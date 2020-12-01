#ifndef WOLFENSTEIN_TALLER1_MACHINE_GUN_H
#define WOLFENSTEIN_TALLER1_MACHINE_GUN_H

#include "items.h"

class MachineGun : public Items {
    public:
        void use() override;
        void remove() override;

    private:
        static int health_recovered;
};


#endif //WOLFENSTEIN_TALLER1_MACHINE_GUN_H
