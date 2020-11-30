#ifndef WOLFENSTEIN_TALLER1_KNIFE_H
#define WOLFENSTEIN_TALLER1_KNIFE_H
#include "gun.h"

class Knife : public Gun {
    public:
        Knife();
        void shoot(Player &shooter) override;
    private:
        int range;
};

#endif //WOLFENSTEIN_TALLER1_KNIFE_H
