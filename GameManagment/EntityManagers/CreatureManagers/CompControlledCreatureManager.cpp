//
// Created by Artem on 02.10.2025.
//

#include "CompControlledCreatureManager.h"

void CompControlledCreatureManager::moveTo(Constants::dxdy dxdy) {
    this->field.getFieldCells()[this->compControlledCreature->getXCoordinate() + dxdy.x][this->compControlledCreature->getYCoordinate() + dxdy.y].addEntityInCell(this->compControlledCreature);
    this->field.getFieldCells()[this->compControlledCreature->getXCoordinate()][this->compControlledCreature->getYCoordinate()].clearCell();
    this->compControlledCreature->setXCoordinate(this->compControlledCreature->getXCoordinate() + dxdy.x);
    this->compControlledCreature->setYCoordinate(this->compControlledCreature->getYCoordinate() + dxdy.y);
}

void CompControlledCreatureManager::attack(Constants::XYPair coordinates) {
    try{
        this->field.getFieldCells()[coordinates.x][coordinates.y].damageEntityInCell(this->compControlledCreature->getDamage());
    }catch (NoEntityInCellNotification &e){
        std::cout << "В клетке по координатам " + std::to_string(coordinates.x) + " " + std::to_string(coordinates.y) + " некого атаковать";
    }
}

int CompControlledCreatureManager::getChanceToDetectHostile() noexcept {
    return this->compControlledCreature->getChanceToDetectHostile();
}