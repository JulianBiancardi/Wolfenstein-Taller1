#ifndef WOLFENSTEIN_TALLER1_FOOD_H
#define WOLFENSTEIN_TALLER1_FOOD_H

#include "items.h"

class Food : public Items {
    public:
        void use() override;
        void remove() override;

    private:
        static int health_recovered;
};


#endif //WOLFENSTEIN_TALLER1_FOOD_H
