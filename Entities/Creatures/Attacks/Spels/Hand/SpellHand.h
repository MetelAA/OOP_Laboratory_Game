//
// Created by Artem on 24.10.2025.
//

#ifndef LABAOOP2_SPELLHAND_H
#define LABAOOP2_SPELLHAND_H

#include "../Spell.h"
#include <vector>
#include <memory>

class SpellHand {
public:


    void addSpell(std::unique_ptr<Spell> spell) noexcept;
    const std::vector<std::unique_ptr<Spell>>& getSpells() const;
    void useSpell(int position); //позиция от 0 до n-1, если используется заклинание улучшения, то фактически улучщается рука а не другое заклинание!


private:
    int gradeLevel;
    std::vector<std::unique_ptr<Spell>> spells;

};


#endif //LABAOOP2_SPELLHAND_H