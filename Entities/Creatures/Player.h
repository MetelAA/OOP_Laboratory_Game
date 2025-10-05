//
// Created by Artem on 22.09.2025.
//

#ifndef LABA1_PLAYER_H
#define LABA1_PLAYER_H

#include "Creature.h"
#include "Attacks/LongRangeAttack.h"
#include "Attacks/CloseRangeAttack.h"

class Player : public Creature {
public:
    Player(int xCoordinate, int yCoordinate, int healthPoint, bool isSlowedFlag,
           CloseRangeAttack &closeRangeAttack, LongRangeAttack &longRangeAttack) :
            Creature(xCoordinate, yCoordinate, healthPoint, EntityType::PlayerEnt, isSlowedFlag),
            closeRangeAttack(closeRangeAttack),
            longRangeAttack(longRangeAttack) {}

    virtual CloseRangeAttack &getCloseRangeAttack() noexcept final; //gets link with modify opportunities
    virtual LongRangeAttack &getLongRangeAttack() noexcept final; //gets link with modify opportunities

protected:
    CloseRangeAttack closeRangeAttack;
    LongRangeAttack longRangeAttack;
};


#endif //LABA1_PLAYER_H
