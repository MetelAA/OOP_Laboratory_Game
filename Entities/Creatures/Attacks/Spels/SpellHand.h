//
// Created by Artem on 24.10.2025.
//

#ifndef LABAOOP2_SPELLHAND_H
#define LABAOOP2_SPELLHAND_H

#include "Spell.h"
#include <vector>

class SpellHand {
public:


    void addSpell(Spell spell) noexcept;
    std::vector<Spell> getSpells() const;
    void useSpell(int position); //позиция от 0 до n-1, если используется заклинание улучшения, то фактически улучщается рука а не другое заклинание!


private:
    int size;
    int buffed; //улучшено ли следующее заклинание, + уровень улучшение (улучшение улучшения)
    std::vector<Spell> spells;

};


#endif //LABAOOP2_SPELLHAND_H