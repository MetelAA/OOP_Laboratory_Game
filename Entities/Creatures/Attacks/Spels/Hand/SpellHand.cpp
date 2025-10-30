//
// Created by Artem on 24.10.2025.
//

#include "SpellHand.h"
//#include "../../../../../Exceptions/UnexpectedBehaviorException.h"

const std::vector<std::unique_ptr<Spell>>& SpellHand::getSpells() const {
    return this->spells;
}

void SpellHand::addSpell(std::unique_ptr<Spell> spell) noexcept {
    this->spells.emplace_back(std::move(spell));
}

void SpellHand::useSpell(int position) {
    if (position < this->spells.size()){
        switch (this->spells.at(position).get()->getSpellType()) {
            case SpellType::DirectDamageSpell:
                break;
            case SpellType::AreaDamageSpell:
                break;
            case SpellType::SummoningSpell:
                break;
            case SpellType::BuffNextUsedSpell:
                break;
            case SpellType::CreateTrapSpell:
                break;
        }
    }else{
        throw UnexpectedBehaviorException("Позиция заклинания выходит за рамки руки?? чтобы это не значило, я уже говорить разучился абоба!");
    }
}
