//
// Created by Artem on 24.09.2025.
//

#include "Cell.h"

CellType Cell::getType() const noexcept{
    return type;
}

bool Cell::hasEntityInCell() const noexcept{
    return this->entityInCell != nullptr;
}

Entity &Cell::getEntityInCell() const {
    return *this->entityInCell;
}

void Cell::addEntityInCell(Entity *entity) noexcept {
    this->entityInCell = entity;
}

void Cell::clearCell() noexcept {
    this->entityInCell = nullptr;
}


