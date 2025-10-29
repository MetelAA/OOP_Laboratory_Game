//
// Created by Artem on 24.10.2025.
//

#include "AreaDamageSpell.h"

int AreaDamageSpell::getDamage(int gradeLevel) const noexcept {
    int level = this->levels.size() < gradeLevel ? gradeLevel : (this->levels.size() - 1);
    return this->levels.at(level).damage;
}

int AreaDamageSpell::getRange(int gradeLevel) const noexcept {
    int level = this->levels.size() < gradeLevel ? gradeLevel : (this->levels.size() - 1);
    return this->levels.at(level).range;
}

int AreaDamageSpell::getAreaRad(int gradeLevel) const noexcept {
    int level = this->levels.size() < gradeLevel ? gradeLevel : (this->levels.size() - 1);
    return this->levels.at(level).areaRad;
}
