//
// Created by Artem on 30.10.2025.
//

#ifndef LABAOOP2_ENEMYDEFENCETOWERCONTROLLER_H
#define LABAOOP2_ENEMYDEFENCETOWERCONTROLLER_H

#include "../EntityManagers/BuildingManagers/EnemyDefenceTowerManager.h"
#include "../GameMaster.h"

class EnemyDefenceTowerController {
public:
    EnemyDefenceTowerController(const Field &field, const EnemyDefenceTowerManager &manager) : field(field),
                                                                                               manager(manager) {}
    void doMove(GameMaster& gameMaster);


private:
    const Field& field;
    EnemyDefenceTowerManager manager;

    std::map<EntityType, bool> typesToAttack = {{EntityType::PlayerEnt, true}, {EntityType::Ally, true}};
    std::vector<EntityType> priorityOfAttack = {EntityType::Ally, EntityType::PlayerEnt};
};


#endif //LABAOOP2_ENEMYDEFENCETOWERCONTROLLER_H
