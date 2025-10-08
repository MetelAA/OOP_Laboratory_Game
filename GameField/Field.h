//
// Created by Artem on 24.09.2025.
//

#ifndef LABA1_FIELD_H
#define LABA1_FIELD_H
#include <vector>
#include <map>
#include "Cell.h"
#include "../Constants/Constants.h"

class Field {
public:

    Field(int W, int H){
        height = W;
        width = H;
    }

    int getWidth() const noexcept; //return data
    int getHeight() const noexcept; //return data
    std::vector<std::vector<Cell>>& getFieldCells() noexcept; //returns instance with modify ability to can modify Cells in vectors
    const std::vector<std::vector<Cell>>& getFieldCells() const noexcept; //returns instance to read or use static Cell methods
    virtual bool canMoveToOrSpawnOn(int dx, int dy) const final;
    virtual std::vector<Constants::XYPair> hasNearEntityOfSomeTypes(std::map<EntityType, bool> types, int x, int y) const noexcept final;

protected:
    int width = 10, height = 10;
    std::vector<std::vector<Cell>> cells;

private:
};


#endif //LABA1_FIELD_H
