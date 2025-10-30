//
// Created by Artem on 24.09.2025.
//

#include "EnemySpawnerBuilding.h"


int EnemySpawnerBuilding::getSpawnInterval() noexcept {
    return this->spawnInterval;
}

std::unique_ptr<Entity> EnemySpawnerBuilding::clone() const {
    return std::make_unique<EnemySpawnerBuilding>(*this);
}
