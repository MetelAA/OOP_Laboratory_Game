//
// Created by Artem on 22.09.2025.
//

#ifndef LABA1_ENEMY_H
#define LABA1_ENEMY_H

#include "Creature.h"

class Enemy : public Creature {
public:
    Enemy(int xCoordinate, int yCoordinate, int healthPoints, int damage) : Creature(xCoordinate, yCoordinate,
                                                                                     healthPoints, EntityType::EnemyEnt),
                                                                            damage(damage) {
    }

private:

protected:
    int damage;
};


#endif //LABA1_ENEMY_H
