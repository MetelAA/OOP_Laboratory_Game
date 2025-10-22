//
// Created by Artem on 22.09.2025.
//

#ifndef LABA1_ENEMY_H
#define LABA1_ENEMY_H

#include "Creature.h"

class Enemy : public Creature {
public:

    Enemy(int xCoordinate, int yCoordinate, int healthPoint, bool isDisabledFlag, int stepRange,
          const int damage, const int chanceToDetectHostile) : Creature(xCoordinate, yCoordinate, healthPoint, EntityType::EnemyEnt,
                                                                        isDisabledFlag, stepRange), damage(damage),
                                                               chanceToDetectHostile(chanceToDetectHostile) {}

    virtual int getDamage() noexcept final;
    virtual int getChanceToDetectHostile() noexcept final;

private:

protected:
    const int damage;
    const int chanceToDetectHostile;
};


#endif //LABA1_ENEMY_H
