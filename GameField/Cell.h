//
// Created by Artem on 24.09.2025.
//

#ifndef LABA1_CELL_H
#define LABA1_CELL_H

#include "../Entities/Entity.h"
#include "CellType.h"

class Cell {
public:
    Cell(int xCoordinate, int yCoordinate, CellType type) : xCoordinate(xCoordinate),yCoordinate(yCoordinate),
                                                                                        type(type){
    }


    int getXCoordinate() const noexcept;
    int getYCoordinate() const noexcept;
    CellType getType() const noexcept;
    bool hasEntityInCell() const noexcept;
    const Entity& getEntityInCell() const noexcept;

private:

protected:
    int xCoordinate, yCoordinate;
    CellType type;
    Entity* entityInCell;


};


#endif //LABA1_CELL_H
