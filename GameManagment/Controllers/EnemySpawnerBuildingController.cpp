//
// Created by Artem on 09.10.2025.
//


#include "EnemySpawnerBuildingController.h"

void EnemySpawnerBuildingController::doMove(GameMaster& gameMaster) {
    std::cout << "Ход, enemySpawnerBuilding: " << &this->manager << std::endl;
    if (this->manager.isTimeToSpawn()){
        EnemyManager spawnedEnemyManager = manager.spawnEnemy();
        manager.resetSpawnCounter();
        EnemyController spawnedEnemyController = EnemyController(spawnedEnemyManager, this->field);

        //!!!!!!!!!!!!!!!!!!!!!! Добавлять копию(?) EnemyController в гей мастер!

        std::cout << "enemySpawnerBuilding: " << &this->manager << " создал нового противника: " << &spawnedEnemyManager << std::endl;
    }else{
        manager.incrementTimeToSpawnCounter();
    }
    std::cout << "enemySpawnerBuilding: " << &this->manager << "закончило ход" << std::endl;
}
