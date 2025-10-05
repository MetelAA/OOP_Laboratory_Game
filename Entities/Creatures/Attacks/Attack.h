//
// Created by Artem on 24.09.2025.
//

#ifndef LABA1_ATTACK_H
#define LABA1_ATTACK_H

#include "AttackType.h"

class Attack {
public:
    Attack(int damage, AttackType type) : damage(damage), type(type) {}

    virtual int getDamage() noexcept final;
    virtual AttackType getType() noexcept final;
private:

protected:
    int damage;
    AttackType type;

};


#endif //LABA1_ATTACK_H
