//
// Created by Artem on 24.10.2025.
//

#include "DirectDamageSpell.h"

int DirectDamageSpell::getDamage() const noexcept {
    return this->damage;
}

int DirectDamageSpell::getRange() const noexcept {
    return this->range;
}
