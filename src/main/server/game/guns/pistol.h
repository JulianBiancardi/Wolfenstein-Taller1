#ifndef WOLFENSTEIN_TALLER1_PISTOL_H
#define WOLFENSTEIN_TALLER1_PISTOL_H
#include "../player.h"
#include "gun.h"

class Pistol : public Gun {
public:
    Pistol();
    void shoot(Player &shooter) override;

private:
    int range;
};

#endif //WOLFENSTEIN_TALLER1_GUN_H
