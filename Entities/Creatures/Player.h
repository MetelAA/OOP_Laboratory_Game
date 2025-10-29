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
           CloseRangeAttack &closeRangeAttack, LongRangeAttack &longRangeAttack, int stepRange) :
            Creature(xCoordinate, yCoordinate, healthPoint, EntityType::PlayerEnt, isSlowedFlag, stepRange),
            closeRangeAttack(closeRangeAttack),
            longRangeAttack(longRangeAttack) {}

    virtual const CloseRangeAttack& getCloseRangeAttack() const noexcept final; //gets link with modify opportunities
    virtual const LongRangeAttack& getLongRangeAttack() const noexcept final; //gets link with modify opportunities
    virtual bool isCloseRangeAttackSelected() const noexcept final;

    std::unique_ptr<Entity> clone() const override;

protected:
    CloseRangeAttack closeRangeAttack;
    LongRangeAttack longRangeAttack;
    bool isCloseRangeAttackSelectedFlag;
};


#endif //LABA1_PLAYER_H
