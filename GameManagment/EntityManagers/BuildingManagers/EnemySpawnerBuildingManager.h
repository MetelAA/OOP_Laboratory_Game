//
// Created by Artem on 05.10.2025.
//

#ifndef LABA1_ENEMYSPAWNERBUILDINGMANAGER_H
#define LABA1_ENEMYSPAWNERBUILDINGMANAGER_H

#include "../../../Entities/Buildings/EnemySpawnerBuilding.h"
#include "../../../GameField/Field.h"
#include "../CreatureManagers/CompControlledCreatureManager.h"
#include "../EntityManager.h"

class EnemySpawnerBuildingManager : public EntityManager{
public:
    EnemySpawnerBuildingManager(Field &field, Entity *entity, EnemySpawner &enemySpawner) : EntityManager(field, entity), building(*dynamic_cast<EnemySpawnerBuilding*>(entity)),
                                                              enemySpawner(enemySpawner) {}

    virtual bool isTimeToSpawn() noexcept final;
    virtual void resetSpawnCounter() noexcept final;
    virtual void incrementTimeToSpawnCounter() noexcept final;
    virtual CompControlledCreatureManager spawnEnemy() final;

protected:
    EnemySpawnerBuilding building;
    EnemySpawner &enemySpawner;
};


#endif //LABA1_ENEMYSPAWNERBUILDINGMANAGER_H
