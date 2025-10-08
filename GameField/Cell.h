//
// Created by Artem on 24.09.2025.
//

#ifndef LABA1_CELL_H
#define LABA1_CELL_H

#include "../Entities/Entity.h"
#include "CellType.h"

class Cell {
public:
    Cell(CellType type) : type(type){}

    CellType getType() const noexcept;

    void addEntityInCell(Entity *entity) noexcept;

    void clearCell() noexcept;

    bool hasEntityInCell() const noexcept;

    Entity& getEntityInCell() const;

private:

protected:
    CellType type;
    Entity *entityInCell;


};


#endif //LABA1_CELL_H
