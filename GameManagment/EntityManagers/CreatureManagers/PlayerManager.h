//
// Created by Artem on 02.10.2025.
//

#ifndef LABA1_PLAYERMANAGER_H
#define LABA1_PLAYERMANAGER_H
#include "CreatureManager.h"
#include "../../../Entities/Creatures/Player.h"
#include <cmath>

class PlayerManager : public CreatureManager{
public:

    void moveTo(Constants::dxdy dxdy) override;
    void attack(Entity &attackWhom, AttackType type);

protected:
    std::shared_ptr<Player> player;
};


#endif //LABA1_PLAYERMANAGER_H
