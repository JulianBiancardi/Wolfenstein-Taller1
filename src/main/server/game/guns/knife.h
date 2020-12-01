#ifndef WOLFENSTEIN_TALLER1_KNIFE_H
#define WOLFENSTEIN_TALLER1_KNIFE_H
#include "gun.h"

class Knife : public Gun {
    public:
        Knife();
        void shoot(Player &shooter) override;

    private:
        const static int range;
        const static int bullet_required = 0;
};

#endif //WOLFENSTEIN_TALLER1_KNIFE_H
