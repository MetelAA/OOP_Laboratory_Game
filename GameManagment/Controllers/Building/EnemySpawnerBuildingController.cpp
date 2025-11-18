//
// Created by Artem on 09.10.2025.
//


#include "EnemySpawnerBuildingController.h"

void EnemySpawnerBuildingController::doMove(GameMaster& gameMaster) {
    std::cout << "Ход, enemySpawnerBuilding: " << &this->manager << std::endl;
    if (this->manager.isTimeToSpawn()){
        manager.resetSpawnCounter();
        CompControlledCreatureManager* spawnedEnemyManager = manager.spawnEnemy();
        EnemyController spawnedEnemyController = EnemyController(this->field, *spawnedEnemyManager);

        //!!!!!!!!!!!!!!!!!!!!!! Добавлять копию EnemyController в гей мастер!

        std::cout << "enemySpawnerBuilding: " << &this->manager << " создал нового противника: " << &spawnedEnemyManager << std::endl;
    }else{
        manager.incrementTimeToSpawnCounter();
    }
    std::cout << "enemySpawnerBuilding: " << &this->manager << "закончило ход" << std::endl;
}
