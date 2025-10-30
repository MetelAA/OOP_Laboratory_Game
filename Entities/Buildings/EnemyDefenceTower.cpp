//
// Created by Artem on 30.10.2025.
//

#include "EnemyDefenceTower.h"

const DirectDamageSpell &EnemyDefenceTower::getDamageSpell() const noexcept {
    return this->spell;
}

int EnemyDefenceTower::getAttackRadius() const noexcept {
    return this->attackRadius;
}

int EnemyDefenceTower::getAttackInterval() const noexcept {
    return this->attackInterval;
}
