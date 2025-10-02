//
// Created by Artem on 24.09.2025.
//

#include "Field.h"

int Field::getWidth() const noexcept {
    return width;
}

int Field::getHeight() const noexcept {
    return height;
}

std::vector<std::vector<Cell>> &Field::getFieldCells() noexcept{
    return cells;
}


