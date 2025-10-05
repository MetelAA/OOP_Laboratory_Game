//
// Created by Artem on 24.09.2025.
//

#ifndef LABA1_FIELD_H
#define LABA1_FIELD_H
#include <vector>
#include "Cell.h"

class Field {
public:

    Field(int W, int H){
        height = W;
        width = H;
    }

    int getWidth() const noexcept; //return data
    int getHeight() const noexcept; //return data
    std::vector<std::vector<Cell>>& getFieldCells() noexcept; //returns instance to modify
    virtual bool canMoveToOrSpawnOn(int dx, int dy) final;

protected:
    int width = 10, height = 10;
    std::vector<std::vector<Cell>> cells;

};


#endif //LABA1_FIELD_H
