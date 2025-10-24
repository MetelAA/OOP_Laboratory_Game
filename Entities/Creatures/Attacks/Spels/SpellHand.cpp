//
// Created by Artem on 24.10.2025.
//

#include "SpellHand.h"

void SpellHand::addSpell(Spell spell) noexcept {
    this->spells.push_back(spell);
}

std::vector<Spell> SpellHand::getSpells() const {
    std::vector<Spell> tempSpells = this->spells;
    if (this->buffed > 0){
        for (int i = 0; i < tempSpells.size(); ++i) {
            switch (tempSpells.at(i).getSpellType()) {
                case SpellType::DirectDamageSpell:
                    break;
                case SpellType::AreaDamageSpell:
                    break;
                case SpellType::SummoningSpell:
                    break;
                case SpellType::BuffNextUsedSpell:
                    break;
            }
        }
    }
    return tempSpells;
}

void SpellHand::useSpell(int position) {
    if (this->spells.at(position).getSpellType() == SpellType::BuffNextUsedSpell)
        this->buffed++;
    else
        this->buffed = 0;
    this->spells.erase(this->spells.begin() + position);
}