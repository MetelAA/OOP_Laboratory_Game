//
// Created by Artem on 09.10.2025.
//

#ifndef LABA1_ENEMYSPAWNERBUILDINGCONTROLLER_H
#define LABA1_ENEMYSPAWNERBUILDINGCONTROLLER_H
#include "../EntityManagers/BuildingManagers/EnemySpawnerBuildingManager.h"

class EnemySpawnerBuildingController {
public:
    EnemySpawnerBuildingController(EnemySpawnerBuildingManager &manager, const Field *field) : manager(manager),
                                                                                               field(field) {}
    void doMove();

protected:
    EnemySpawnerBuildingManager& manager;
    const Field* field;
};


#endif //LABA1_ENEMYSPAWNERBUILDINGCONTROLLER_H
