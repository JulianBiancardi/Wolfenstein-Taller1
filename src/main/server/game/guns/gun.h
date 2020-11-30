#ifndef WOLFENSTEIN_TALLER1_GUN_H
#define WOLFENSTEIN_TALLER1_GUN_H
#include "../player.h"

class Gun {
    public:
        Gun();
        virtual void shoot(Player& shooter);

    private:
        static int bullet_required;
        static int base_precision;
};

#endif //WOLFENSTEIN_TALLER1_GUN_H
