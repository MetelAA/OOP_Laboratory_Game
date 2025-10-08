//
// Created by Artem on 05.10.2025.
//

#include "EnemySpawner.h"


Enemy& EnemySpawner::createEnemy(int x, int y) {
    try{
        this->field.canMoveToOrSpawnOn(x, y);
        Enemy *enemy = new Enemy(x, y, enemyModel.healthPoint, this->field.getFieldCells()[x][y].getType() == CellType::Slowing, enemyModel.damage);
        this->field.getFieldCells()[x][y].addEntityInCell(enemy);
        return *enemy;
    }catch (CellImpassableException& ex){
        throw SpawnEntityException(std::string("Can't spawn enemy because: ") + ex.what());
    }catch (CoordinateException& ex){
        throw SpawnEntityException(std::string("Can't spawn enemy because: ") + ex.what());
    }
}
