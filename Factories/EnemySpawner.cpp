//
// Created by Artem on 05.10.2025.
//

#include "EnemySpawner.h"


Enemy& EnemySpawner::createEnemy(int x, int y) {
    try{
        this->field.canMoveToOrSpawnOn(x, y);
        Enemy *enemy = new Enemy(x, y, enemyModel.healthPoint,
                                 this->field.getFieldCells()[x][y].getCellType() == CellType::Slowing, enemyModel.damage, enemyModel.stepCount, enemyModel.chanceToDetectHostile);
        this->field.getFieldCells()[x][y].addEntityInCell(enemy);
        return *enemy;
    }catch (CellImpassableNotification& ex){
        throw SpawnEntityException(std::string("Can't spawn enemy because: ") + ex.what());
    }catch (CoordinateException& ex){
        throw SpawnEntityException(std::string("Can't spawn enemy because: ") + ex.what());
    }
}
