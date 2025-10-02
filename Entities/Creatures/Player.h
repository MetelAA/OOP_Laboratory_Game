//
// Created by Artem on 22.09.2025.
//

#ifndef LABA1_PLAYER_H
#define LABA1_PLAYER_H
#include "Creature.h"

class Player : public Creature{
public:
    Player(int xCoordinate, int yCoordinate, int healthPoints) : Creature(xCoordinate, yCoordinate,
                                                                                  healthPoints, EntityType::PlayerEnt) {}
};


#endif //LABA1_PLAYER_H
