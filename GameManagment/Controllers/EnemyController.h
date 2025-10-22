//
// Created by Artem on 08.10.2025.
//

#ifndef LABA1_ENEMYCONTROLLER_H
#define LABA1_ENEMYCONTROLLER_H
#include "../EntityManagers/CreatureManagers/EnemyManager.h"
#include "../../GameField/Field.h"
#include "../../Exceptions/UnexpectedBehaviorException.h"
#include "../../Exceptions/Notifications/SlowingCellNotification.h"
#include <queue>
#include <stack>
#include <iostream>
#include <utility>

class EnemyController {
public:
    EnemyController(EnemyManager manager, const Field &field) : manager(std::move(manager)), field(field) {}

    void doMove();

protected:
    EnemyManager manager;
    const Field& field;

private:
    void moveTo(std::stack<Constants::XYPair> trip);
    std::map<EntityType, bool> typesToAttack = {{EntityType::PlayerEnt, true}};
    std::vector<EntityType> priorityOfAttack = {EntityType::PlayerEnt};

    struct EntityCoordsWithNearestPositionToAttackFrom{
        Constants::XYPair attackFromCoordinates;
        Constants::XYPair entityCoordinates;
    };

    EntityCoordsWithNearestPositionToAttackFrom chooseByPriority(std::vector<EntityCoordsWithNearestPositionToAttackFrom>& enemyWithNearestPositionToAttack, std::vector<std::vector<int>>& distances);
};


#endif //LABA1_ENEMYCONTROLLER_H
