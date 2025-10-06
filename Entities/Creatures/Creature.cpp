
#include "Creature.h"



void Creature::setYCoordinate(int y) noexcept{
    this->yCoordinate = y;
}

void Creature::setXCoordinate(int x) noexcept{
    this->xCoordinate = x;
}

bool Creature::isSlowed() noexcept {
    return isSlowedFlag;
}

