//
// Created by Artem on 24.09.2025.
//

#include "Field.h"
#include "../Exceptions/CoordinateException.h"
#include "../Exceptions/Notifications/CellImpassableNotification.h"

int Field::getWidth() const noexcept {
    return width;
}

int Field::getHeight() const noexcept {
    return height;
}

std::vector<std::vector<Cell>> &Field::getFieldCells() noexcept {
    return cells;
}


bool Field::canMoveToOrSpawnOn(int x, int y) const {
    if (x < 0 || x >= this->width) {
        throw CoordinateException{"x coordinate must be between 0 and "
                                  + std::to_string(this->width)
                                  + " but x is "
                                  + std::to_string(x)
                                  + '\n'};
    }

    if (y < 0 || y >= this->height) {
        throw CoordinateException{"y coordinate must be between 0 and "
                                  + std::to_string(this->height)
                                  + " but y is "
                                  + std::to_string(y)
                                  + '\n'};
    }

    Cell fieldCell = this->cells[x][y];

    if (fieldCell.getCellType() != CellType::Impassable) {
        throw CellImpassableNotification("cell is impassible, wall or something sht like that");
    }

    if (fieldCell.hasEntityInCell() && fieldCell.getEntityInCell().getType() == EntityType::EnemyBuildingEnt) {
        throw CellImpassableNotification("cell is occupied by compControlledCreature building");
    }

    return true;
}

std::vector<Constants::XYPair> Field::hasNearEntityOfSomeTypes(std::map<EntityType, bool> types, int x, int y) const noexcept { //возварщает координаты стоящих в радиусе атаки Entity определённых типов
    std::vector<Constants::XYPair> result;
    for (Constants::dxdy pair : Constants::dxdys) {
        if ((x + pair.x) >= 0 && (x + pair.x) < this->width
        && (y + pair.y) >= 0 && (y + pair.y) < this->height) {
            if (this->cells[x + pair.x][y + pair.y].hasEntityInCell() &&
                types.count(this->cells[x + pair.x][y + pair.y].getEntityInCell().getType()) > 0) {
                result.push_back({x + pair.x, y + pair.y});
            }
        }
    }
    return result;
}

const std::vector<std::vector<Cell>> &Field::getFieldCells() const noexcept {
    return this->cells;
}

bool Field::canMoveToOrSpawnOnNoExcept(int x, int y) const noexcept {
    try {
        return this->canMoveToOrSpawnOn(x, y);
    }catch (...) {
        return false;
    }
}

std::vector<Constants::XYPair>
Field::hasNearEntityOfSomeTypesWithAChance(std::map<EntityType, bool> types, int x, int y, int chance) const noexcept {
    std::vector<Constants::XYPair> result = this->hasNearEntityOfSomeTypes(types, x, y);
    for (auto it = result.begin(); it != result.end(); ) {
        if((rand() % 101) < chance){
            it = result.erase(it);
        } else {
            ++it;
        }
    }

    return result;
}

