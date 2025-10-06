//
// Created by Artem on 24.09.2025.
//

#include "Field.h"
#include "../Exceptions/CoordinateException.h"
#include "../Exceptions/CellImpassableException.h"

int Field::getWidth() const noexcept {
    return width;
}

int Field::getHeight() const noexcept {
    return height;
}

std::vector<std::vector<Cell>> &Field::getFieldCells() noexcept {
    return cells;
}


bool Field::canMoveToOrSpawnOn(int x, int y) {
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

    if (fieldCell.getType() != CellType::Impassable) {
        throw CellImpassableException("cell is impassible, wall or something sht like that");
    }

    if (fieldCell.hasEntityInCell() && fieldCell.getEntityInCell().getType() == EntityType::EnemyBuildingEnt) {
        throw CellImpassableException("cell is occupied by enemy building");
    }

    return true;
}

std::vector<std::pair<int, int>>
Field::hasNearEntityOfSomeTypes(std::map<EntityType, bool> types, int x, int y) noexcept {
    std::vector<std::pair<int, int>> result;
    for (std::pair<int, int> pair: this->dxdys) {
        if ((x + pair.first) >= 0 && (x + pair.first) < this->width && (y + pair.second) >= 0 &&
            (y + pair.second) < this->height) {
            if (this->cells[x + pair.first][y + pair.second].hasEntityInCell() &&
                types.count(this->cells[x + pair.first][y + pair.second].getEntityInCell().getType()) > 0) {
                result.emplace_back(x + pair.first, y + pair.second);
            }
        }
    }
    return result;
}