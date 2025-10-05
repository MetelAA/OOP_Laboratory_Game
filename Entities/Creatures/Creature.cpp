
#include "Creature.h"




bool Creature::isAlive() noexcept{
    return this->healthPoint > 0;
}

void Creature::setYCoordinate(int y) noexcept{
    this->yCoordinate = y;
}

void Creature::setXCoordinate(int x) noexcept{
    this->xCoordinate = x;
}

int Creature::getHP() noexcept {
    return this->healthPoint;
}

bool Creature::isSlowed() noexcept {
    return isSlowedFlag;
}

