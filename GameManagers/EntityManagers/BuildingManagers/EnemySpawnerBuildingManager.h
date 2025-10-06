//
// Created by Artem on 05.10.2025.
//

#ifndef LABA1_ENEMYSPAWNERBUILDINGMANAGER_H
#define LABA1_ENEMYSPAWNERBUILDINGMANAGER_H

#include "../../../Entities/Buildings/EnemySpawnerBuilding.h"
#include "../../../GameField/Field.h"
#include "../CreatureManagers/EnemyManager.h"
#include "../EntityManager.h"

class EnemySpawnerBuildingManager : public EntityManager{
public:
    EnemySpawnerBuildingManager(Field &field, EnemySpawnerBuilding &building, EnemySpawner &enemySpawner)
            : EntityManager(field), building(building), enemySpawner(enemySpawner) {}

    virtual bool isTimeToSpawn() noexcept final;
    virtual void incrementTimeToSpawnCounter() noexcept final;
    virtual EnemyManager spawnEnemy() final;

    bool checkEntityStatus() override;


protected:
    EnemySpawnerBuilding &building;
    EnemySpawner &enemySpawner;


private:
    const std::vector<std::pair<int, int>> dxdy{{-1, 1},
                                                {0,  1},
                                                {1,  1},
                                                {1,  0},
                                                {1,  -1},
                                                {0,  -1},
                                                {-1, -1},
                                                {-1, 0}};
};


#endif //LABA1_ENEMYSPAWNERBUILDINGMANAGER_H
