//
// Created by Artem on 24.09.2025.
//

#include "Attack.h"

AttackType Attack::getType() noexcept {
    return type;
}

int Attack::getDamage() noexcept {
    return damage;
}
