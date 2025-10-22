//
// Created by Artem on 02.10.2025.
//

#include "EnemyManager.h"

void EnemyManager::moveTo(Constants::dxdy dxdy) {
    this->field.getFieldCells()[this->enemy.getXCoordinate() + dxdy.x][this->enemy.getYCoordinate() + dxdy.y].addEntityInCell(&this->enemy);
    this->field.getFieldCells()[this->enemy.getXCoordinate()][this->enemy.getYCoordinate()].clearCell();
    this->enemy.setXCoordinate(this->enemy.getXCoordinate() + dxdy.x);
    this->enemy.setYCoordinate(this->enemy.getYCoordinate() + dxdy.y);
}

void EnemyManager::attack(Constants::XYPair coordinates) {
    try{
        this->field.getFieldCells()[coordinates.x][coordinates.y].damageEntityInCell(this->enemy.getDamage());
    }catch (NoEntityInCellNotification &e){
        std::cout << "В клетке по координатам " + std::to_string(coordinates.x) + " " + std::to_string(coordinates.y) + " некого атаковать";
    }
}

int EnemyManager::getChanceToDetectHostile() noexcept {
    return this->enemy.getChanceToDetectHostile();
}