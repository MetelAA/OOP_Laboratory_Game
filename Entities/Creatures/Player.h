//
// Created by Artem on 22.09.2025.
//

#ifndef LABA1_PLAYER_H
#define LABA1_PLAYER_H

#include "Creature.h"
#include "Attacks/LongRangeAttack.h"
#include "Attacks/CloseRangeAttack.h"
#include "Attacks/Spels/Hand/SpellHand.h"

class Player : public Creature {
public:
    Player(int xCoordinate, int yCoordinate, int healthPoint, bool isSlowedFlag,
           CloseRangeAttack &closeRangeAttack, LongRangeAttack &longRangeAttack, int stepRange, int score,
           SpellHand &hand) :
            Creature(xCoordinate, yCoordinate, healthPoint, EntityType::PlayerEnt, isSlowedFlag, stepRange),
            closeRangeAttack(closeRangeAttack), longRangeAttack(longRangeAttack), score(score), hand(hand) {}

    Player(Player &&other) noexcept
            : Creature(std::move(other)),
              closeRangeAttack(std::move(other.closeRangeAttack)),
              longRangeAttack(std::move(other.longRangeAttack)),
              isCloseRangeAttackSelectedFlag(other.isCloseRangeAttackSelectedFlag),
              score(other.score),
              hand(std::move(other.hand)) {}

    Player(const Player &other)
            : Creature(other),
              closeRangeAttack(other.closeRangeAttack),
              longRangeAttack(other.longRangeAttack),
              isCloseRangeAttackSelectedFlag(other.isCloseRangeAttackSelectedFlag),
              score(other.score),
              hand(other.hand) {}

    virtual const CloseRangeAttack &getCloseRangeAttack() const noexcept final;
    virtual const LongRangeAttack &getLongRangeAttack() const noexcept final;
    virtual bool isCloseRangeAttackSelected() const noexcept final;
    virtual void changeSelectedAttackType() noexcept final;

    virtual long getScore() const noexcept final;
    virtual SpellHand& getSpellHand() noexcept final;

    std::unique_ptr<Entity> clone() const override;


protected:
    CloseRangeAttack closeRangeAttack;
    LongRangeAttack longRangeAttack;
    bool isCloseRangeAttackSelectedFlag;
    long score;
    SpellHand hand;
};


#endif //LABA1_PLAYER_H
