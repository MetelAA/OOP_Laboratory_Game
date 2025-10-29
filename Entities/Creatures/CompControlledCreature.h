//
// Created by Artem on 22.09.2025.
//

#ifndef LABA1_ENEMY_H
#define LABA1_ENEMY_H

#include "Creature.h"

class CompControlledCreature : public Creature {
public:

    CompControlledCreature(int xCoordinate, int yCoordinate, int healthPoint, EntityType type, bool isDisabledFlag,
                           int stepRange, const int damage, const int chanceToDetectHostile) :
            Creature(xCoordinate, yCoordinate, healthPoint, type, isDisabledFlag, stepRange),
            damage(damage), chanceToDetectHostile(chanceToDetectHostile) {}

    virtual int getDamage() noexcept final;
    virtual int getChanceToDetectHostile() noexcept final;

    std::unique_ptr<Entity> clone() const override;

private:

protected:
    const int damage;
    const int chanceToDetectHostile;
};


#endif //LABA1_ENEMY_H
