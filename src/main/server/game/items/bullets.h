#ifndef WOLFENSTEIN_TALLER1_BULLETS_H
#define WOLFENSTEIN_TALLER1_BULLETS_H

#include "items.h"

class Bullets : public Items{
public:
    void use() override;
    void remove() override;

private:
    static int amount;
};


#endif //WOLFENSTEIN_TALLER1_BULLETS_H
