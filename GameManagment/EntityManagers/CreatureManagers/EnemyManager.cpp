//
// Created by Artem on 02.10.2025.
//

#include <queue>
#include "EnemyManager.h"

void EnemyManager::moveTo(Constants::dxdy dxdy) {
    this->field.getFieldCells()[this->enemy.getXCoordinate() + dxdy.x][this->enemy.getYCoordinate() + dxdy.y].addEntityInCell(&this->enemy);
    this->field.getFieldCells()[this->enemy.getXCoordinate()][this->enemy.getYCoordinate()].clearCell();
    this->enemy.setXCoordinate(this->enemy.getXCoordinate() + dxdy.x);
    this->enemy.setYCoordinate(this->enemy.getYCoordinate() + dxdy.y);
}

void EnemyManager::attack(Entity &attackWhom) {
    attackWhom.changeHealthPoints((-1) * this->enemy.getDamage());
}