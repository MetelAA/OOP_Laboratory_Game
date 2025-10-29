//
// Created by Artem on 24.09.2025.
//

#ifndef LABA1_ENEMYSPAWNERBUILDING_H
#define LABA1_ENEMYSPAWNERBUILDING_H

#include "../../Factories/EnemySpawner.h"
#include "Building.h"

class EnemySpawnerBuilding : public Building {
public:
    EnemySpawnerBuilding(int xCoordinate, int yCoordinate, int healthPoint, int spawnInterval,
                         int stepCounter) : Building(xCoordinate, yCoordinate, healthPoint,
                                                     EntityType::EnemyBuildingEnt), spawnInterval(spawnInterval),
                                            stepCounter(stepCounter) {}

    virtual void incrementStepCounter() noexcept final;

    virtual int getStepCounter() noexcept final;

    virtual void resetSpawnCounter() noexcept final;

    virtual int getSpawnInterval() noexcept final;

    std::unique_ptr<Entity> clone() const override;

protected:
    int spawnInterval, stepCounter = 0;
};


#endif //LABA1_ENEMYSPAWNERBUILDING_H
