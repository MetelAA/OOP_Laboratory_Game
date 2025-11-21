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
    PlayerManager(Field &field, std::shared_ptr<Player>& player) : CreatureManager(field, player.get()),
                                                                   player(player) {}
    void moveTo(Constants::dxdy dxdy) override;
    void attack(Constants::dxdy coords, AttackType type);
    bool isCloseRangeAttackSelected() const noexcept;
    int getLongRangeAttackRange() const noexcept;
    void changeAttackType() noexcept;
    std::string getAttackTypeStr() noexcept;
    AttackType getAttackType() noexcept;
    const std::vector<std::unique_ptr<Spell>>& getSpells() noexcept;
    SpellHand& getSpellHand();

protected:
    std::shared_ptr<Player> player;
};


#endif //LABA1_PLAYERMANAGER_H
