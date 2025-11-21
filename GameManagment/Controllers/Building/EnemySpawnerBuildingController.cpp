//
// Created by Artem on 09.10.2025.
//


#include "EnemySpawnerBuildingController.h"
#include "../../GameMaster.h"

void EnemySpawnerBuildingController::doMove(GameMaster& gameMaster) {
    std::cout << "Ход, enemySpawnerBuilding: " << this << std::endl;
    if (this->manager.isTimeToSpawn()){
        std::cout << "enemySpawnerBuilding: " << this << " создаёт нового противнка" << std::endl;
        manager.resetSpawnCounter();
        manager.spawnEnemy();
        gameMaster.redraw();
        std::cout << "enemySpawnerBuilding: " << this << " новый противник успешно создан" << std::endl;
    }else{
        std::cout << "enemySpawnerBuilding: " << this << " находиться на cooldown" << std::endl;
        manager.incrementTimeToSpawnCounter();
    }
    std::cout << "enemySpawnerBuilding: " << this << " закончило ход" << std::endl;
}

bool EnemySpawnerBuildingController::isAlive() {
    return this->manager.isAlive();
}
