#ifndef WOLFENSTEIN_TALLER1_KEY_H
#define WOLFENSTEIN_TALLER1_KEY_H

#include "items.h"

class Key : public Items{
public:
    Key();
    void use() override;
    void remove() override;


};



#endif //WOLFENSTEIN_TALLER1_KEY_H
