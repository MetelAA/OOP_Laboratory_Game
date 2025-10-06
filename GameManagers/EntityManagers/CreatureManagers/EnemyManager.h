//
// Created by Artem on 02.10.2025.
//

#ifndef LABA1_ENEMYMANAGER_H
#define LABA1_ENEMYMANAGER_H
#include "../../../Entities/Creatures/Enemy.h"
#include "CreatureManager.h"
#include "../../../Entities/Creatures/Player.h"

class EnemyManager : public CreatureManager{
public:
    EnemyManager(Field &field, Enemy &enemy) : CreatureManager(field), enemy(enemy) {}


protected:
    Enemy &enemy;

private:
    std::map<EntityType, bool> typesToAttack = {{EntityType::PlayerEnt, true}};

};


#endif //LABA1_ENEMYMANAGER_H
