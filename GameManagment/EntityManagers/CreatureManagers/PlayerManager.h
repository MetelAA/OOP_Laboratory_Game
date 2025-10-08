//
// Created by Artem on 02.10.2025.
//

#ifndef LABA1_PLAYERMANAGER_H
#define LABA1_PLAYERMANAGER_H
#include "CreatureManager.h"
#include "../../../Entities/Creatures/Player.h"

class PlayerManager : public CreatureManager{
public:

    void moveTo(Constants::dxdy dxdy) override;

    void attack(Entity &attackWhom, AttackType type);

    int getStepRange() override;

protected:
    Player& player;

};


#endif //LABA1_PLAYERMANAGER_H
