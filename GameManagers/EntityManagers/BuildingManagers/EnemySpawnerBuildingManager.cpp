//
// Created by Artem on 05.10.2025.
//

#include "EnemySpawnerBuildingManager.h"

bool EnemySpawnerBuildingManager::isTimeToSpawn() noexcept {
    return this->building.getStepCounter() == this->building.getSpawnInterval();
}

std::pair<int, int> chooseDxDy(std::vector<std::pair<int, int>> &dxdys) {
    int ind = rand() % dxdys.size();
    std::pair<int, int> pair = dxdys.at(ind);
    dxdys.erase(dxdys.begin() + ind);
    return pair;
}

EnemyManager EnemySpawnerBuildingManager::spawnEnemy() {
    this->building.resetSpawnCounter();
    std::vector<std::pair<int, int>> dxdyCopy = this->dxdy;

    while (!dxdyCopy.empty()) {
        try{
            std::pair<int, int> pair = chooseDxDy(dxdyCopy);

            Enemy& enemy = this->enemySpawner.createEnemy(this->building.getXCoordinate() + pair.first,
                                                   this->building.getYCoordinate() + pair.second);
            return EnemyManager(this->field, enemy);
        }catch (){

        }
    }


}

void EnemySpawnerBuildingManager::incrementTimeToSpawnCounter() noexcept {
    this->building.incrementStepCounter();
}

bool EnemySpawnerBuildingManager::checkEntityStatus() {
    return this->building.isAlive();
}


