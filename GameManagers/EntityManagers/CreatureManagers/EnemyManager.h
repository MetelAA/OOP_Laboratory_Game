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
    void doMove();

    struct DataToMove{
        int x, y, stepsCount;
    };
protected:

    Enemy &enemy;
    std::vector<DataToMove> canMoveTo(); //название метода сомнительное. должен давать координаты в которые может (должен) перместиться enemy
    virtual void moveTo(std::pair<int, int> coordinates) final;


private:
    std::map<EntityType, bool> typesToAttack = {{EntityType::PlayerEnt, true}};
    std::vector<EntityType> priorityOfAttack = {EntityType::PlayerEnt};
};


#endif //LABA1_ENEMYMANAGER_H
