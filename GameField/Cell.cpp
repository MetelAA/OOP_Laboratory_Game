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

const Entity &Cell::getEntityInCell() const noexcept{
    return *entityInCell;
}

bool Cell::hasEntityInCell() const noexcept{
    return entityInCell != nullptr;
}

