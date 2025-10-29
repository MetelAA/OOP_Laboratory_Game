//
// Created by Artem on 24.10.2025.
//

#ifndef LABAOOP2_CREATETRAPSPELL_H
#define LABAOOP2_CREATETRAPSPELL_H

#include "Spell.h"
#include "../../../../GameField/CellEvents/TrapCellEvent.h"
#include <memory>
#include <map>

class CreateTrapSpell : public Spell {
    CreateTrapSpell() : Spell(SpellType::CreateTrapSpell) {} //инфа почему так в диркет дамаге

    virtual std::unique_ptr<TrapCellEvent> getTrapCellEvent(int gradeLevel) const final;


private:
    struct levelInfo{
        int damage;
    };
    const std::map<int, levelInfo> levels = {{0, {2}},
                                             {1, {4}},
                                             {2, {6}},
                                             {3, {8}}
    };
};


#endif //LABAOOP2_CREATETRAPSPELL_H
