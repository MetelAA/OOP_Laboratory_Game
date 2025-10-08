//
// Created by Artem on 08.10.2025.
//

#ifndef LABA1_ENEMYCONTROLLER_H
#define LABA1_ENEMYCONTROLLER_H
#include "../EntityManagers/CreatureManagers/EnemyManager.h"
#include "../../GameField/Field.h"
#include "../../Exceptions/ChooseEnemyPriorityException.h"

class EnemyController {
public:
    EnemyController(EnemyManager &manager, const Field &field) : manager(manager), field(field) {}

    void doMove();

protected:
    EnemyManager& manager;
    const Field& field;

private:
    std::map<EntityType, bool> typesToAttack = {{EntityType::PlayerEnt, true}};
    std::vector<EntityType> priorityOfAttack = {EntityType::PlayerEnt};

    struct EntityWithNearestPositionToAttackFrom{
        Constants::XYPair attackFromCoordinates;
        Constants::XYPair entityCoordinates;
    };

    EntityWithNearestPositionToAttackFrom chooseByPriority(std::vector<EntityWithNearestPositionToAttackFrom>& enemyWithNearestPositionToAttack, std::vector<std::vector<int>>& distances);
};


#endif //LABA1_ENEMYCONTROLLER_H
