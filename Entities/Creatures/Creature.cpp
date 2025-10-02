
#include "Creature.h"


void Creature::getHP(int dHealth) noexcept{
    this->healthPoints + dHealth;
}

bool Creature::isAlive() noexcept{
    return this->healthPoints > 0;
}

void Creature::setYCoordinate(int y) noexcept{
    this->yCoordinate = y;
}

void Creature::setXCoordinate(int x) noexcept{
    this->xCoordinate = x;
}
