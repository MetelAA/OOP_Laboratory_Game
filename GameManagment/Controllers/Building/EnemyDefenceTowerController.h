//
// Created by Artem on 30.10.2025.
//

#ifndef LABAOOP2_ENEMYDEFENCETOWERCONTROLLER_H
#define LABAOOP2_ENEMYDEFENCETOWERCONTROLLER_H

#include "../../EntityManagers/BuildingManagers/EnemyDefenceTowerManager.h"
class GameMaster;

class EnemyDefenceTowerController {
public:
    EnemyDefenceTowerController(const Field &field, const EnemyDefenceTowerManager &manager) : field(field),
                                                                                               manager(manager) {}
    void doMove(GameMaster& gameMaster);
    bool isAlive();

private:
    const Field& field;
    EnemyDefenceTowerManager manager;

    std::map<EntityType, int> typesToAttackWithPriority = {{EntityType::PlayerEnt, 1}, {EntityType::Ally, 2}};

    struct CreatureWithDistance{
        EntityType creatureType;
        int distance;
        Constants::XYPair coords;
    };
};


#endif //LABAOOP2_ENEMYDEFENCETOWERCONTROLLER_H
