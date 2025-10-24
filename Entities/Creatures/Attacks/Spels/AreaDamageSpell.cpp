//
// Created by Artem on 24.10.2025.
//

#include "AreaDamageSpell.h"

int AreaDamageSpell::getDamage() const noexcept {
    return this->damage;
}

int AreaDamageSpell::getRange() const noexcept {
    return this->range;
}

int AreaDamageSpell::getAreaRad() const noexcept {
    return this->areaRad;
}
