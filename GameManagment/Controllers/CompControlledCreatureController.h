//
// Created by Artem on 23.10.2025.
//

#ifndef LABAOOP2_COMPCONTROLLEDCREATURECONTROLLER_H
#define LABAOOP2_COMPCONTROLLEDCREATURECONTROLLER_H
#include "../EntityManagers/CreatureManagers/CompControlledCreatureManager.h"
#include "../../GameField/Field.h"
#include "../../Exceptions/UnexpectedBehaviorException.h"
#include "../../Exceptions/Notifications/SlowingCellNotification.h"
#include <queue>
#include <stack>
#include <iostream>
#include <utility>

class CompControlledCreatureController {
public:
    CompControlledCreatureController(const Field &field,
                                     CompControlledCreatureManager manager): field(field), manager(std::move(manager)) {}

    void computeAndDoMove(std::map<EntityType, bool>& typesToAttack, std::vector<EntityType>& priorityOfAttack);
private:
    const Field& field;
    CompControlledCreatureManager manager;

    void moveTo(std::stack<Constants::XYPair> trip, std::string headerCout);
//    std::map<EntityType, bool> typesToAttack = {{EntityType::PlayerEnt, true}};
//    std::vector<EntityType> priorityOfAttack = {EntityType::PlayerEnt};

    struct EntityCoordsWithNearestPositionToAttackFrom{
        Constants::XYPair attackFromCoordinates;
        Constants::XYPair entityCoordinates;
    };

    EntityCoordsWithNearestPositionToAttackFrom chooseByPriority(std::vector<EntityCoordsWithNearestPositionToAttackFrom> &enemyWithNearestPositionToAttack, std::vector<std::vector<int>>& distances, std::vector<EntityType>& priorityOfAttack);
};


#endif //LABAOOP2_COMPCONTROLLEDCREATURECONTROLLER_H
