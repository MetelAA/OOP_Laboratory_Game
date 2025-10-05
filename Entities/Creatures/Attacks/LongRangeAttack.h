//
// Created by Artem on 03.10.2025.
//

#ifndef LABA1_LONGRANGEATTACK_H
#define LABA1_LONGRANGEATTACK_H
#include "Attack.h"

class LongRangeAttack : Attack{
public:
    LongRangeAttack(int damage, int range) : Attack(damage, AttackType::LongRange), range(range){}
protected:
    int range;
};


#endif //LABA1_LONGRANGEATTACK_H
