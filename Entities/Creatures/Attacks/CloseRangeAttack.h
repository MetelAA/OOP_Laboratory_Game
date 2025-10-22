//
// Created by Artem on 03.10.2025.
//

#ifndef LABA1_CLOSERANGEATTACK_H
#define LABA1_CLOSERANGEATTACK_H
#include "Attack.h"

class CloseRangeAttack : public Attack{
public:
    CloseRangeAttack(int damage) : Attack(damage, AttackType::CloseRange){}

};


#endif //LABA1_CLOSERANGEATTACK_H
