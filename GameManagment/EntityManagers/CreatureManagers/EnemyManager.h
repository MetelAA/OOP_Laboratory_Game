//
// Created by Artem on 02.10.2025.
//

#ifndef LABA1_ENEMYMANAGER_H
#define LABA1_ENEMYMANAGER_H
#include "../../../Entities/Creatures/Enemy.h"
#include "CreatureManager.h"
#include "../../../Entities/Creatures/Player.h"
#include "../../../Constants/Constants.h"
#include <iostream>

class EnemyManager : public CreatureManager{
public:
    EnemyManager(Field &field, Creature *creature) : CreatureManager(field, creature), enemy(*dynamic_cast<Enemy*>(creature)) {}

    void moveTo(Constants::dxdy dxdy) override;

    virtual void attack(Constants::XYPair coordinates);

    virtual int getChanceToDetectHostile() noexcept final;

protected:
    Enemy enemy;
};


#endif //LABA1_ENEMYMANAGER_H
