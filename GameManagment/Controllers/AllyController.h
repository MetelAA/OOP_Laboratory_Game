//
// Created by Artem on 23.10.2025.
//

#ifndef LABAOOP2_ALLYCONTROLLER_H
#define LABAOOP2_ALLYCONTROLLER_H
#include "CompControlledCreatureController.h"

class AllyController : public CompControlledCreatureController{
    AllyController(const Field &field, const CompControlledCreatureManager &manager): CompControlledCreatureController(field, manager) {}

    void doMove();

private:
    std::map<EntityType, bool> typesToAttack = {{EntityType::EnemyEnt, true}, {EntityType::EnemyBuildingEnt, true}};
    std::vector<EntityType> priorityOfAttack = {EntityType::EnemyEnt, EntityType::EnemyBuildingEnt};
};


#endif //LABAOOP2_ALLYCONTROLLER_H
