#ifndef WOLFENSTEIN_TALLER1_ROCKET_LAUNCHER_H
#define WOLFENSTEIN_TALLER1_ROCKET_LAUNCHER_H

#include "items.h"

class RocketLauncher : public Items{
    public:
        RocketLauncher();
        void use() override;
        void remove() override;

    private:
        static int health_recovered;
};


#endif //WOLFENSTEIN_TALLER1_ROCKET_LAUNCHER_H
