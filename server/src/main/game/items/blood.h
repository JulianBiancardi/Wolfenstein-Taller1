#ifndef WOLFENSTEIN_TALLER1_BLOOD_H
#define WOLFENSTEIN_TALLER1_BLOOD_H

#include "items.h"

class Blood : public Items{
    public:
        Blood();
        void use() override;
        void remove() override;

    private:
        static int health_recovered;
        static int less_than;
};


#endif //WOLFENSTEIN_TALLER1_BLOOD_H
