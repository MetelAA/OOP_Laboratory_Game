//
// Created by Artem on 24.09.2025.
//

#include "Cell.h"

int Cell::getXCoordinate() const noexcept{
    return xCoordinate;
}

int Cell::getYCoordinate() const noexcept{
    return yCoordinate;
}

CellType Cell::getType() const noexcept{
    return type;
}

bool Cell::hasEntityInCell() const noexcept{
    return this->entityInCell != nullptr;
}

Entity &Cell::getEntityInCell() const {
    return *this->entityInCell;
}

void Cell::setEntityInCell(Entity *entity) noexcept {
    this->entityInCell = entity;
}


