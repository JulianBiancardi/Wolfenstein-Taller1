#ifndef WOLFENSTEIN_TALLER1_MEDIC_KIT_H
#define WOLFENSTEIN_TALLER1_MEDIC_KIT_H

#include "items.h"

class MedicKit : public Items{
    public:
        void use() override;
        void remove() override;

    private:
        static int health_recovered;
};


#endif //WOLFENSTEIN_TALLER1_MEDIC_KIT_H
