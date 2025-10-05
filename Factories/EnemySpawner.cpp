//
// Created by Artem on 05.10.2025.
//

#include "EnemySpawner.h"


Enemy EnemySpawner::createEnemy(int x, int y, bool isSlowed) {

    try{
        this->field.canMoveToOrSpawnOn(x, y);
        return Enemy(x, y, enemyModel.healthPoint, isSlowed, enemyModel.damage);
    }catch (CellImpassableException& ex){
        ex.what();
        throw CanNotSpawnEntityException("Can't spawn enemy because: " + ex.what());
    }catch (CoordinateException& ex){

    }


}
