//
// Created by Artem on 22.09.2025.
//

#include "CompControlledCreature.h"

int CompControlledCreature::getDamage() noexcept {
    return damage;
}

int CompControlledCreature::getChanceToDetectHostile() noexcept {
    return chanceToDetectHostile;
}
