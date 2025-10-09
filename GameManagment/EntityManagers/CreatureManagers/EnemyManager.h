//
// Created by Artem on 02.10.2025.
//

#ifndef LABA1_ENEMYMANAGER_H
#define LABA1_ENEMYMANAGER_H
#include "../../../Entities/Creatures/Enemy.h"
#include "CreatureManager.h"
#include "../../../Entities/Creatures/Player.h"
#include "../../../Constants/Constants.h"

class EnemyManager : public CreatureManager{
public:
    EnemyManager(Field &field, Entity *entity) : CreatureManager(field, entity), enemy(*dynamic_cast<Enemy*>(entity)) {}

    void moveTo(Constants::dxdy dxdy) override;

    virtual void attack(Entity& attackWhom);

    int getStepRange() const noexcept override;


protected:
    Enemy &enemy;

};


#endif //LABA1_ENEMYMANAGER_H
