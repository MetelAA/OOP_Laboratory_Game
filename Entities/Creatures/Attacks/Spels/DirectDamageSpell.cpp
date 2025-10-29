//
// Created by Artem on 24.10.2025.
//

#include "DirectDamageSpell.h"

int DirectDamageSpell::getDamage(int gradeLevel) const noexcept {
    if (gradeLevel < this->levels.size()){
        return this->levels.at(gradeLevel).damage;
    }else{
        return this->levels.at(levels.size() - 1).damage;
    }
}

int DirectDamageSpell::getRange(int gradeLevel) const noexcept {
    if (gradeLevel < this->levels.size()){
        return this->levels.at(gradeLevel).range;
    }else{
        return this->levels.at(levels.size() - 1).range;
    }
}
