//
// Created by Artem on 24.10.2025.
//

#include "SpellHand.h"
//#include "../../../../../Exceptions/UnexpectedBehaviorException.h"
#include "../SpellOnCoords.h"
#include <iostream>

const std::vector<std::unique_ptr<Spell>>& SpellHand::getSpells() const {
    return this->spells;
}

void SpellHand::addSpell(std::unique_ptr<Spell> spell) noexcept {
    this->spells.emplace_back(std::move(spell));
}

void SpellHand::useSpellWithoutAnyCoordsBinding(int position) {
    this->checkSpellPositionAvailability(position);
    switch (this->spells.at(position).get()->getSpellType()) {
        case SpellType::BuffNextUsedSpell:
            this->gradeLevel++;
            this->spells.at(position).release();
            this->spells.erase(this->spells.begin() + position);
            std::cout << "Использовано заклинание улучшения, уровень следующего заклинания: " << (this->gradeLevel + 1) << std::endl;
        case SpellType::DirectDamageSpell:
        case SpellType::AreaDamageSpell:
        case SpellType::SummoningSpell:
        case SpellType::CreateTrapSpell:
            throw UnexpectedBehaviorException("Выбран не правильный метод для использования заклинания этого типа");
    }
}

void SpellHand::useSpellWithAIMBinding(int position, Field& field, Constants::XYPair from, Constants::XYPair to) {
    this->checkSpellPositionAvailability(position);
    switch (this->spells.at(position).get()->getSpellType()) {
        case SpellType::DirectDamageSpell:
        case SpellType::AreaDamageSpell:
        case SpellType::SummoningSpell:
        case SpellType::CreateTrapSpell:
        {
            SpellOnCoords* spell = dynamic_cast<SpellOnCoords*>(this->spells.at(position).get());
            spell->castSpell(this->gradeLevel, field, from, to);
            this->gradeLevel = 1;
        }
            break;
        case SpellType::BuffNextUsedSpell:
            throw UnexpectedBehaviorException("Выбран не правильный метод для использования заклинания этого типа");
    }

}

bool SpellHand::checkSpellPositionAvailability(int position) const {
    if (position < this->spells.size()){
        return true;
    }else{
        throw UnexpectedBehaviorException("Позиция заклинания выходит за рамки руки?? чтобы это не значило, я уже говорить разучился абоба!");
    }
}
