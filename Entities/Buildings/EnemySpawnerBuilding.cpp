//
// Created by Artem on 24.09.2025.
//

#include "EnemySpawnerBuilding.h"

int EnemySpawnerBuilding::getStepCounter() noexcept {
    return this->stepCounter;
}

void EnemySpawnerBuilding::incrementStepCounter() noexcept {
    this->stepCounter++;
}

void EnemySpawnerBuilding::resetSpawnCounter() noexcept {
    this->stepCounter = 0;
}

int EnemySpawnerBuilding::getSpawnInterval() noexcept {
    return this->spawnInterval;
}

std::unique_ptr<Entity> EnemySpawnerBuilding::clone() const {
    return std::make_unique<EnemySpawnerBuilding>(*this);
}
