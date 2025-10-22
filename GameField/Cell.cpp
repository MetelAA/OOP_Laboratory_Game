//
// Created by Artem on 24.09.2025.
//

#include "Cell.h"

CellType Cell::getCellType() const noexcept{
    return type;
}

bool Cell::hasEntityInCell() const noexcept{
    return this->entityInCell != nullptr;
}

void Cell::addEntityInCell(Entity *entity) noexcept {
    this->entityInCell = entity;
}

void Cell::clearCell() noexcept {
    this->entityInCell = nullptr;
}

void Cell::damageEntityInCell(int damage) {
    if (this->entityInCell != nullptr){
        this->entityInCell->changeHealthPoints((-1) * damage);
    }
    throw NoEntityInCellNotification("В клетке нету сущности");
}

EntityType Cell::getEntityInCellType() const {
    if (this->entityInCell != nullptr){
        return this->entityInCell->getType();
    }
    throw NoEntityInCellNotification("В клетке нету сущности");
}

Entity &Cell::getEntityInCell() const noexcept {
    return *this->entityInCell;
}


