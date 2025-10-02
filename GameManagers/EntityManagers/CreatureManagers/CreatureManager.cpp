//
// Created by Artem on 02.10.2025.
//

#include "CreatureManager.h"

void CreatureManager::moveTo(int dx, int dy) {
    int newX = this->creature.getXCoordinate() + dx;
    int newY = this->creature.getYCoordinate() + dy;
    if(canMoveTo(newX, newY)){
        this->creature.setXCoordinate(newX);
        this->creature.setYCoordinate(newY);
    }else
        throw CoordinateException("unknown coordinate exception");
}

bool CreatureManager::canMoveTo(int dx, int dy) {
    int newX = this->creature.getXCoordinate() + dx;
    int newY = this->creature.getYCoordinate() + dy;
    if (newX < 0 || newX >= this->field.getWidth()){
        throw CoordinateException{"x coordinate must be between 0 and "
                                  + std::to_string(this->field.getWidth())
                                  + " but newX is "
                                  + std::to_string(newX)
                                  + '\n'};
    }

    if (newY < 0 || newY >= this->field.getHeight()){
        throw CoordinateException{"y coordinate must be between 0 and "
                                  + std::to_string(this->field.getHeight())
                                  + " but newY is "
                                  + std::to_string(newX)
                                  + '\n'};
    }

    Cell fieldCell = field.getFieldCells()[newX][newY];

    if (fieldCell.getType() != CellType::Impassable){
        throw CellImpassableException("cell is impassible, wall or something sht like that");
    }

    if (fieldCell.hasEntityInCell() && fieldCell.getEntityInCell().getType() == EntityType::EnemyBuildingEnt){
        throw CellImpassableException("cell is occupied by enemy building");
    }

    return true;
}

