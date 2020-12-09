#ifndef WOLFENSTEIN_TALLER1_DAMAGABLE_H
#define WOLFENSTEIN_TALLER1_DAMAGABLE_H


class Damagable {
    public:
        virtual void receive_damage(int amount) = 0;
};


#endif //WOLFENSTEIN_TALLER1_DAMAGABLE_H
