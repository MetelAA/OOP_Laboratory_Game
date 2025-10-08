//
// Created by Artem on 22.09.2025.
//

#ifndef LABA1_ENEMY_H
#define LABA1_ENEMY_H

#include "Creature.h"

class Enemy : public Creature {
public:
    Enemy(int xCoordinate, int yCoordinate, int healthPoint, bool isSlowedFlag, int damage, int stepRange) : Creature(
            xCoordinate, yCoordinate, healthPoint, EntityType::EnemyEnt, isSlowedFlag, stepRange), damage(damage) {}

    virtual int getDamage() noexcept final;

private:

protected:
    int damage;
};


#endif //LABA1_ENEMY_H
