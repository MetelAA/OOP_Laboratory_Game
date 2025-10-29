//
// Created by Artem on 24.10.2025.
//

#include "CreateTrapSpell.h"

std::unique_ptr<TrapCellEvent> CreateTrapSpell::getTrapCellEvent(int gradeLevel) const {
    int level = gradeLevel < this->levels.size() ? gradeLevel : (this->levels.size()-1);
    auto* trap = new TrapCellEvent(this->levels.at(level).damage);
    return std::make_unique<TrapCellEvent>(*trap);
}
