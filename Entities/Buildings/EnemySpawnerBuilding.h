//
// Created by Artem on 24.09.2025.
//

#ifndef LABA1_ENEMYSPAWNERBUILDING_H
#define LABA1_ENEMYSPAWNERBUILDING_H
#include "../../Factories/EnemySpawner.h"


class EnemySpawnerBuilding {
public:


protected:
    int spawnInterval, stepCounter = 0;
    EnemySpawner& enemySpawner;

};


#endif //LABA1_ENEMYSPAWNERBUILDING_H
