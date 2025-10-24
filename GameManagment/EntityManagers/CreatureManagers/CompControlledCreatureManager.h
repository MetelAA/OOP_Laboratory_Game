//
// Created by Artem on 02.10.2025.
//

#ifndef LABA1_ENEMYMANAGER_H
#define LABA1_ENEMYMANAGER_H
#include "../../../Entities/Creatures/CompControlledCreature.h"
#include "CreatureManager.h"
#include "../../../Entities/Creatures/Player.h"
#include "../../../Constants/Constants.h"
#include <iostream>

class CompControlledCreatureManager : public CreatureManager{
public:
    CompControlledCreatureManager(Field &field, Creature *creature) : CreatureManager(field, creature), compControlledCreature(*dynamic_cast<CompControlledCreature*>(creature)) {}

    void moveTo(Constants::dxdy dxdy) override;

    virtual void attack(Constants::XYPair coordinates);

    virtual int getChanceToDetectHostile() noexcept final;

protected:
    CompControlledCreature compControlledCreature;
};


#endif //LABA1_ENEMYMANAGER_H
